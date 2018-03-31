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

#include "krunner_filesearch.h"

// KF
#include <KLocalizedString>

krunner_filesearch::krunner_filesearch(QObject *parent, const QVariantList &args)
    : Plasma::AbstractRunner(parent, args)
{
    setObjectName("krunner_filesearch");
}

krunner_filesearch::~krunner_filesearch()
{
}


void krunner_filesearch::match(Plasma::RunnerContext &context)
{
    const QString term = context.query();
    if (term.length() < 3) {
        return;
    }

    // TODO
}

void krunner_filesearch::run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match)
{
    Q_UNUSED(context)
    Q_UNUSED(match)

    // TODO
}

K_EXPORT_PLASMA_RUNNER(krunner_filesearch, krunner_filesearch)

// needed for the QObject subclass declared as part of K_EXPORT_PLASMA_RUNNER
#include "krunner_filesearch.moc"
