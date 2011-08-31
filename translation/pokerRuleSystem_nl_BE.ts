<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.0" language="nl_BE">
<context>
<<<<<<< HEAD
    <name>CardEvaluator</name>
    <message>
        <location filename="../ui_cardEvaluator.h" line="186"/>
        <source>card evaluator</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../ui_cardEvaluator.h" line="187"/>
        <source>add card</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../ui_cardEvaluator.h" line="188"/>
        <source>delete card</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../ui_cardEvaluator.h" line="189"/>
        <source>add value</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../ui_cardEvaluator.h" line="190"/>
        <source>Selecteer een (on)gelijkheid uit de lijst en de gewenste waarde van de kaart. Als de waarde een variabele is, kan er gekozen worden voor een postfix. Een variabele begint altijd met een kleine letter.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../ui_cardEvaluator.h" line="191"/>
        <source>Kleur:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../ui_cardEvaluator.h" line="194"/>
        <source>?</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../ui_cardEvaluator.h" line="195"/>
        <source>hearts</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../ui_cardEvaluator.h" line="196"/>
        <source>clubs</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../ui_cardEvaluator.h" line="197"/>
        <source>spades</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../ui_cardEvaluator.h" line="198"/>
        <source>diamonds</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../ui_cardEvaluator.h" line="200"/>
        <source>Selecteer een kleur uit de lijst of type een variabele in. Een variabele begint altijd met een kleine letter. </source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../ui_cardEvaluator.h" line="201"/>
        <source>0</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../ui_cardEvaluator.h" line="202"/>
        <source>Operator</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../ui_cardEvaluator.h" line="203"/>
        <source>Waarde</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../ui_cardEvaluator.h" line="204"/>
        <source>Postfix</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../ui_cardEvaluator.h" line="205"/>
        <source>save</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../ui_cardEvaluator.h" line="206"/>
        <source>cancel</source>
=======
    <name>Translator</name>
    <message>
        <location filename="../src/lib/pokerRuleSystem/raiseaction.cpp" line="37"/>
        <source>raise</source>
        <translation>raise</translation>
    </message>
    <message>
        <location filename="../src/lib/pokerRuleSystem/types.cpp" line="37"/>
        <source>numerical</source>
        <translation>numerisch</translation>
    </message>
    <message>
        <location filename="../src/lib/pokerRuleSystem/types.cpp" line="42"/>
        <source>cardList</source>
        <translation>kaartlijst</translation>
    </message>
    <message>
        <location filename="../src/lib/pokerRuleSystem/types.cpp" line="47"/>
        <source>cardEquation</source>
        <translation>kaartvergelijking</translation>
    </message>
    <message>
        <source>unknownType</source>
        <translation type="obsolete">onbekend</translation>
    </message>
    <message>
        <source>boolean</source>
        <translation type="obsolete">booleaans</translation>
    </message>
    <message>
        <source>void</source>
        <translation type="obsolete">leeg</translation>
    </message>
</context>
<context>
    <name>poker::card::CardExpressionValidator</name>
    <message>
        <source>error at location %i</source>
        <translation type="obsolete">Fout op positie %i</translation>
    </message>
    <message>
        <location filename="../src/lib/pokerRuleSystem/card/cardexpressionvalidator.cpp" line="66"/>
        <source>error at location %1</source>
        <translation>Fout op positie %1</translation>
    </message>
</context>
<context>
    <name>poker::view::CardEditWidget</name>
    <message>
        <location filename="../../../build/poker/src/lib/pokerRuleSystem/ui_cardeditwidget.h" line="196"/>
        <source>Form</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../../../build/poker/src/lib/pokerRuleSystem/ui_cardeditwidget.h" line="198"/>
        <source>Voor kleur kies je oftewel een van elementen uit de lijst, oftewel een variabele welke met een kleine letter begint, zoals: kleurX</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../../../build/poker/src/lib/pokerRuleSystem/ui_cardeditwidget.h" line="199"/>
        <source>Kleur:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../../../build/poker/src/lib/pokerRuleSystem/ui_cardeditwidget.h" line="200"/>
        <source>=</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../../../build/poker/src/lib/pokerRuleSystem/ui_cardeditwidget.h" line="201"/>
        <source>Voor waarde kies je eerst een (on)-gelijkheid (&lt;, &lt;=, =, &gt; &gt;=) en dan oftewel
a) een waarde (2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K, A)
b) een variabele (ook met een kleine letter)
Bij een variabele kan je ook nog + of - een waarde toevoegen.
Vb: =A (een aas); =kaartX (variabele genaamd kaartX); &gt;6 (kaart groter dan een 6) </source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../../../build/poker/src/lib/pokerRuleSystem/ui_cardeditwidget.h" line="206"/>
        <source>Waarde:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../../../build/poker/src/lib/pokerRuleSystem/ui_cardeditwidget.h" line="207"/>
        <source>Toevoegen</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../../../build/poker/src/lib/pokerRuleSystem/ui_cardeditwidget.h" line="208"/>
        <source>Verwijderen</source>
>>>>>>> 11188477aa0df7aafbf7af4f2f2319259f11b7c0
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
<<<<<<< HEAD
    <name>Translator</name>
    <message>
        <location filename="../../../../../src/lib/pokerRuleSystem/raiseaction.cpp" line="39"/>
        <source>raise</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../../../../../src/lib/pokerRuleSystem/types.cpp" line="37"/>
        <source>numerical</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../../../../../src/lib/pokerRuleSystem/types.cpp" line="42"/>
        <source>cardList</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../../../../../src/lib/pokerRuleSystem/types.cpp" line="47"/>
        <source>cardEquation</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>poker::AllCards</name>
    <message>
        <location filename="../../../../../src/lib/pokerRuleSystem/dictionary/featureDictionary.hpp" line="14"/>
        <source>all cards</source>
=======
    <name>poker::view::EditBoolDialog</name>
    <message>
        <location filename="../src/lib/pokerRuleSystem/view/editbooldialog.cpp" line="40"/>
        <source>waar</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lib/pokerRuleSystem/view/editbooldialog.cpp" line="41"/>
        <source>onwaar</source>
>>>>>>> 11188477aa0df7aafbf7af4f2f2319259f11b7c0
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
<<<<<<< HEAD
    <name>poker::card::CardExpressionValidator</name>
    <message>
        <location filename="../../../../../src/lib/pokerRuleSystem/card/cardexpressionvalidator.cpp" line="66"/>
        <source>error at location %1</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>poker::view::EditBoolDialog</name>
    <message>
        <location filename="../../../../../src/lib/pokerRuleSystem/view/editbooldialog.cpp" line="39"/>
        <source>waar</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../../../../../src/lib/pokerRuleSystem/view/editbooldialog.cpp" line="40"/>
        <source>onwaar</source>
        <translation type="unfinished"></translation>
=======
    <name>poker::view::EditCardListDialog</name>
    <message>
        <location filename="../../../build/poker/src/lib/pokerRuleSystem/ui_editcardlistdialog.h" line="118"/>
        <source>Dialog</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../../../build/poker/src/lib/pokerRuleSystem/ui_editcardlistdialog.h" line="119"/>
        <source>Insert New Card</source>
        <translation>Voeg kaart toe</translation>
    </message>
    <message>
        <location filename="../../../build/poker/src/lib/pokerRuleSystem/ui_editcardlistdialog.h" line="120"/>
        <source>Delete Selected Card</source>
        <translation>Verwijder kaart</translation>
>>>>>>> 11188477aa0df7aafbf7af4f2f2319259f11b7c0
    </message>
</context>
<context>
    <name>poker::view::EditConstantDialog</name>
    <message>
<<<<<<< HEAD
        <location filename="../ui_editconstantdialog.h" line="99"/>
=======
        <location filename="../../../build/poker/src/lib/pokerRuleSystem/ui_editconstantdialog.h" line="99"/>
>>>>>>> 11188477aa0df7aafbf7af4f2f2319259f11b7c0
        <source>Dialog</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
<<<<<<< HEAD
        <location filename="../ui_editconstantdialog.h" line="100"/>
=======
        <location filename="../../../build/poker/src/lib/pokerRuleSystem/ui_editconstantdialog.h" line="100"/>
>>>>>>> 11188477aa0df7aafbf7af4f2f2319259f11b7c0
        <source>waarde:</source>
        <translation type="unfinished"></translation>
    </message>
</context>
</TS>
