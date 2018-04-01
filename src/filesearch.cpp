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
#include <Baloo/IndexerConfig>
#include <KRunner/QueryMatch>

#include <QDebug>
#include <QDir>
#include <QUrl>
#include <QMimeData>
#include <QMimeDatabase>

FileSearchRunner::FileSearchRunner(QObject *parent, const QVariantList &args)
    : Plasma::AbstractRunner(parent, args)
{
    setIgnoredTypes(
        Plasma::RunnerContext::NetworkLocation |
        Plasma::RunnerContext::Executable |
        Plasma::RunnerContext::ShellCommand
    );
    setSpeed(Plasma::AbstractRunner::SlowSpeed);
}

FileSearchRunner::~FileSearchRunner()
{
}


void FileSearchRunner::match(Plasma::RunnerContext &context)
{
    if (context.query().length() < 3) {
        return;
    }

    Baloo::Query query;
    query.setSearchString(context.query());
    query.setType("");
    query.setLimit(10);

    Baloo::ResultIterator it = query.exec();

    QMimeDatabase mimeDb;

    float relevance = 0.8;
    while (it.next()) {
        QString localUrl = it.filePath();
        const QUrl url = QUrl::fromLocalFile(localUrl);

        if (!localUrl.contains(context.query(), Qt::CaseInsensitive)) {
            return;
        }

        Plasma::QueryMatch match;

        match.setId(it.filePath());
        match.setData(it.filePath());
        match.setText(url.fileName());

        match.setIconName(mimeDb.mimeTypeForFile(localUrl).iconName());
        match.setMatchCategory("File");

        if (localUrl.compare(context.query(), Qt::CaseInsensitive)) {
            match.setRelevance(1.0);
            match.setType(Plasma::QueryMatch::ExactMatch);
        } else {
            match.setRelevance(relevance);
            match.setType(Plasma::QueryMatch::PossibleMatch);
        }

        QString folderPath = url.adjusted(QUrl::RemoveFilename | QUrl::StripTrailingSlash).toLocalFile();
        if (folderPath.startsWith(QDir::homePath())) {
            folderPath.replace(0, QDir::homePath().length(), QStringLiteral("~"));
        }

        match.setSubtext(folderPath);
        relevance -= 0.05;

        context.addMatch(match);
    }
}

void FileSearchRunner::run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match)
{
    Q_UNUSED(context)

    const QUrl url = QUrl::fromLocalFile(match.data().toString());
    KRun *opener = new KRun(url, 0);
    opener->setRunExecutables(false);
}

K_EXPORT_PLASMA_RUNNER(FileSearchRunner, FileSearchRunner)

// needed for the QObject subclass declared as part of K_EXPORT_PLASMA_RUNNER
#include "filesearch.moc"

