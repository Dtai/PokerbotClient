/*******************************************************************
* Copyright (c) 2010 Thomas Fannes (thomasfannes@gmail.com)
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

#include "elementserializer.hpp"
#include "../../element.hpp"
#include "../../feature.hpp"
#include "../../function.hpp"
#include "../../constant.hpp"
#include "../../dbwrapper.hpp"
#include "../../calculatorfactory.hpp"
#include <QMap>
#include <boost/shared_ptr.hpp>
#include "../../exception.hpp"

using namespace ruleSystem;

namespace serialization
{
namespace qt
{
namespace
{
QMap<QString, boost::shared_ptr<ElementSerializer> > & serializersMap()
{
    static QMap<QString, boost::shared_ptr<ElementSerializer> > map;
    return map;
}
}

ElementSerializer::ElementSerializer()
{
}

ElementSerializer::~ElementSerializer()
{
}

void ElementSerializer::RegisterSerializer(ElementSerializer * serializer)
{
    if(serializer == 0)
        return;

    serializersMap()[serializer->identifier().name()] = boost::shared_ptr<ElementSerializer>(serializer);
}

const ElementSerializer * ElementSerializer::FindSerializer(const QString & name)
{
    QMap<QString, boost::shared_ptr<ElementSerializer> >::iterator i = serializersMap().find(name);
    if(i == serializersMap().end())
        return 0;
    else
        return i.value().get();
}

const ElementSerializer * ElementSerializer::FindSerializer(Element * element)
{
    if(element == 0)
        return 0;

    return FindSerializer(element->typeID().name());
}



ruleSystem::Element * FeatureSerializer::deserialize(QDataStream & stream) const
{
	QString n, d, devName;
    Type t;
    DBWrapper w;

	stream >> t >> n >> devName >> w >> d;

    Feature * f = new Feature(t, n);
    f->setDB(w.db());
    f->setDescription(d);
	f->setDevName(devName);

    return f;
}
void FeatureSerializer::serialize(QDataStream & stream, ruleSystem::Element * element) const
{
    Feature * f = element_cast<Feature>(element);

    DBWrapper w(f->db());

	stream << f->type() << f->name() << f->devName() << w << f->description();

}


ruleSystem::Element * FunctionSerializer::deserialize(QDataStream & stream) const
{
    QString n, d;
    const Calculator * c;
    QList<Element*> e;

    stream >> c >> e >> d;
    Function * f = new Function(c);
    f->setDescription(d);
    for(int i = 0; i < e.size(); i++)
        f->setFunctionInput(i, e.at(i));


    return f;
}
void FunctionSerializer::serialize(QDataStream & stream, ruleSystem::Element * element) const
{
    Function * f = element_cast<Function>(element);

    stream << f->calculator() << f->functionInputs() << f->description();
}

Element * ConstantSerializer::deserialize(QDataStream & stream) const
{
    QString d;
    Type t;
    QVariant v;

    stream >> d >> t >> v;

    Constant * c = new Constant(t);
    c->setValue(v);
    c->setDescription(d);

    return c;
}

void ConstantSerializer::serialize(QDataStream & stream, Element *element) const
{
    Constant * c = element_cast<Constant>(element);
    stream << c->description() << c->type() << c->value();
}

}
}

using namespace serialization::qt;

QDataStream & operator<<(QDataStream & stream, ruleSystem::Element* element)
{
    if(element == 0)
    {
        stream << QString();
        return stream;
    }

    const ElementSerializer * s = ElementSerializer::FindSerializer(element);

    if(s == 0)
        throw Exception(Exception::tr("Unable to find a valid serializer"), Exception::tr("ElementSerializer::FindSerializer"));


    stream << element->typeID().name();
    s->serialize(stream, element);

    return stream;
}

QDataStream & operator>>(QDataStream & stream, ruleSystem::Element * & element)
{
    element = 0;
    QString name;
    stream >> name;

    if(name == QString())
    {
        element = 0;
        return stream;
    }

    const ElementSerializer * s = ElementSerializer::FindSerializer(name);
    if(s == 0)
        throw Exception(Exception::tr("Unable to find a valid deserializer"), Exception::tr("ElementSerializer::FindSerializer"));


    element = s->deserialize(stream);

    return stream;
}



