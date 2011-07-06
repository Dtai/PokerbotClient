/*******************************************************************
* Copyright (c) 2009 Thomas Fannes (thomasfannes@gmail.com)
*
* Permission is hereby granted, free of charge, to any person
* obtaining a copy of this software and associated documentation
* files (the "Software"), to deal in the Software without
* restriction, including without limitation the rights to use,
* copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following
* conditions:
*
* The above copyright notice and this permission notice shall be
* included in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
* OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
* HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
* OTHER DEALINGS IN THE SOFTWARE.
*******************************************************************/

#include "feature.hpp"
#include "dbwrapper.hpp"

namespace ruleSystem
{
        TYPEID_INHERIT_SOURCE("Feature", Evaluatable, Feature)

	Feature::Feature(const Type & type, const QString & name)
		: Evaluatable(type, name),
		_db(0)
	{
	}

	Feature * Feature::clone() const
	{
		Feature * f = new Feature(type(), name());
		f->setDB(db());

		return f;
	}

	bool Feature::isCorrect(QString * errorMessage) const
	{
		if(name().isEmpty())
		{
			ErrorMsg(errorMessage, tr("This feature has no name"));
			return false;
		}

		if(db() == 0)
		{
			ErrorMsg(errorMessage, tr("This feature has no valid database"));
			return false;

		}

		if(!db()->hasFeature(name()))
		{
			ErrorMsg(errorMessage, QString(tr("The feature \'%1\' is unknown")).arg(name()));
			return false;
		}

		ErrorMsg(errorMessage, "");
		return true;
	}

	QVariant Feature::calculateValue()
	{
		if(db() == 0)
			return QVariant();
		else
			return db()->getFeatureValue(name());
	}

	Type Feature::inputType(const QString & /*inputPosition*/, bool & isValid) const
	{
		isValid = false;

		return Type();

	}
}
