/*
   Copyright %{CURRENT_YEAR} by %{AUTHOR} <%{EMAIL}>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef KRUNNER_FILESEARCH_H
#define KRUNNER_FILESEARCH_H

#include <KRunner/AbstractRunner>
#include <QAction>

class FileSearchRunner : public Plasma::AbstractRunner
{
    Q_OBJECT

public:
    FileSearchRunner(QObject* parent, const QVariantList& args);
    ~FileSearchRunner();
    void match(Plasma::RunnerContext &context) override;
    void run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match) override;
    QList<QAction *> actionsForMatch(const Plasma::QueryMatch &match) override;

protected:
    void init() override;

private:
    QIcon mIcon;
    QList<QAction *> actionList;

};

#endif
