/*
 * This file is based on baloosearchrunner.cpp from the KDE Baloo Project
 *
 * Original work:
 *      Copyright (C) 2014 Vishesh Handa <me@vhanda.in>
 *      Copyright (C) 2017 David Edmundson <davidedmundson@kde.org>
 *
 * Modified work:
 *      Copyright (C) 2018 Daniel Wutke <dwu.public@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include "filesearch.h"

#include <KLocalizedString>
#include <KRun>

#include <Baloo/Query>
#include <KRunner/QueryMatch>

#include <QAction>
#include <QIcon>
#include <QDir>
#include <QUrl>
#include <QMimeDatabase>

K_EXPORT_PLASMA_RUNNER(filesearch, FileSearchRunner)

static const QString s_openFileId = QStringLiteral("openFile");
static const QString s_openFolderId = QStringLiteral("openFolder");

FileSearchRunner::FileSearchRunner(QObject *parent, const QVariantList &args)
    : Plasma::AbstractRunner(parent, args)
{
    mIcon = QIcon::fromTheme("utilities-terminal");
    setObjectName(QString("filesearch"));
    setSpeed(NormalSpeed);
    setPriority(HighestPriority);

    auto comment = i18n("Looks for a file matching :q:. Pressing ENTER opens the file.");
    setDefaultSyntax(Plasma::RunnerSyntax(QString(":q:"), comment));
}

FileSearchRunner::~FileSearchRunner()
{
}

void FileSearchRunner::init()
{
    QAction* openFolderAction = addAction(s_openFolderId, QIcon::fromTheme(QStringLiteral("document-open-folder")), i18n("Open Folder"));
    openFolderAction->setData(s_openFolderId);
    actionList << openFolderAction;

    QAction* openFileAction = addAction(s_openFileId, QIcon::fromTheme(QStringLiteral("text-x-plain")), i18n("Open File"));
    openFileAction->setData(s_openFileId);
    actionList << openFileAction;
}

void FileSearchRunner::match(Plasma::RunnerContext &context)
{
    if (context.query().length() < 3) {
        return;
    }

    if (!context.isValid()) {
        return;
    }

    Baloo::Query query;
    query.setSearchString(context.query());
    query.setLimit(-1);

    QMimeDatabase mimeDb;
    QList<Plasma::QueryMatch> matches;

    Baloo::ResultIterator it = query.exec();
    while (it.next()) {
        QString localUrl = it.filePath();
        const QUrl url = QUrl::fromLocalFile(localUrl);

        // Skip result if not all query tokens found in baloo match
        QStringList queryTokens = context.query().split(' ', QString::SkipEmptyParts);
        bool allTokensFound = true;
        foreach (const QString &queryToken, queryTokens) {
            if (!localUrl.contains(queryToken, Qt::CaseInsensitive)) {
                allTokensFound = false;
                break;
            }
        }

        if (!allTokensFound) {
            continue;
        }

        // Prepare and return match
        Plasma::QueryMatch match(this);

        match.setId(it.filePath());
        match.setData(url);
        match.setText(url.fileName());
        match.setIconName(mimeDb.mimeTypeForFile(localUrl).iconName());
        match.setMatchCategory("File");
        match.setRelevance(1);
        match.setType(Plasma::QueryMatch::ExactMatch);

        QString folderPath = url.adjusted(QUrl::RemoveFilename | QUrl::StripTrailingSlash).toLocalFile();
        if (folderPath.startsWith(QDir::homePath())) {
            folderPath.replace(0, QDir::homePath().length(), QStringLiteral("~"));
        }

        match.setSubtext(folderPath);

        matches.append(match);
    }

    context.addMatches(matches);
}

void FileSearchRunner::run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match)
{
    Q_UNUSED(context)

    const QUrl url = match.data().toUrl();
    if (match.selectedAction() != NULL) {
        const auto action = match.selectedAction()->data();
        if (action == s_openFileId) {
            KRun *opener = new KRun(url, 0);
            opener->setRunExecutables(false);
        } else if (action == s_openFolderId) {
            QFileInfo fi(url.toLocalFile());
            KRun *opener = new KRun(QUrl::fromLocalFile(fi.absolutePath()), 0);
            opener->setRunExecutables(false);
        }
    }
}

QList<QAction *> FileSearchRunner::actionsForMatch(const Plasma::QueryMatch &match)
{
    Q_UNUSED(match)

    return actionList;
}

#include "filesearch.moc"

