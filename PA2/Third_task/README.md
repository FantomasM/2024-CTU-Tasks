<td class="header"><b>Intervaly</b></td>

<td class="lrtbCell" colspan="3" align="left"><p>Úkolem je realizovat třídy <tt>CRange</tt> a <tt>CRangeList</tt>, která budou reprezentovat 
celočíselné intervaly a jejich seznamy.</p>

<p>Předpokládáme intervaly celých čísel. Interval může obsahovat pouze jedno číslo, nebo více čísel.
Jednoprvkové intervaly budeme zapisovat pouze jako jedno číslo, tedy např. <tt>42</tt>. Víceprvkové 
intervaly pak v lomených závorkách. Např. interval <tt>&lt;1..5&gt;</tt> obsahuje 
čísla <tt>1,2,3,4,5</tt>. Interval celých čísel implementuje třída <tt>CRange</tt>. Protože chceme 
pracovat s velkým rozsahem čísel, bude tato třída ukládat meze intervalu jako čísla typu 
<tt>long long</tt> (chceme pracovat i se zápornými čísly). Rozhraní <tt>CRange</tt> je:</p>
<dl>
  <dt>konstruktor (lo, hi)</dt><dd>inicializuje instanci na interval v rozsahu <tt>lo</tt> až 
    <tt>hi</tt>. Konstruktor kontroluje, že <tt>lo &le; hi</tt>. Pokud podmínka není splněna, 
    bude hozena výjimka <tt>std::logic_error</tt> (standardní výjimka z hlavičkového souboru <tt>stdexcept</tt>).</dd>
  <dt>další</dt><dd>Další rozhraní odvoďte podle konstrukcí z přiloženého ukázkového kódu, můžete si samozřejmě přidat 
    i další metody závislé na vaší implementaci. Je pouze potřeba dodržet velikost instance - max. 2x velikost 
    <tt>long long</tt>.</dd>
</dl>    

<p>Třída <tt>CRangeList</tt> bude reprezentovat seznam takových intervalů. Při skládání intervalů do 
instance <tt>CRangeList</tt> budeme ukládat intervaly tak kompaktně, jak to jen lze. Tedy například 
sousedící nebo překrývající se intervaly sloučíme do jednoho delšího intervalu. Instance 
<tt>CRangeList</tt> bude nabízet rozhraní pro vkládání intervalů, odebírání intervalů, testování 
hodnoty a výstup. V bonusovém testu bude třída dále nabízet další rozhraní pro zjednodušení používání 
(viz dále). Konkrétní požadované rozhraní bude:</p>

<dl>
  <dt>implicitní konstruktor</dt><dd>inicializuje prázdný seznam intervalů</dd>
  <dt>destruktor, kopírující konstruktor, op=</dt><dd>budou implementované, pokud 
    jsou zapotřebí a pokud automaticky generovaná podoba nestačí. Doporučujeme použít vhodný 
    kontejner pro ukládání intervalů a kopírování a přesouvání ponechat na automaticky 
    generovaném kódu.</dd>
    
  <dt><tt>includes(long long) / includes (CRange)</tt></dt><dd>metody zjistí, zda seznam intervalů 
    obsahuje zadanou hodnotu / celý zadaný interval hodnot. Pokud ano, vrací <tt>true</tt>, pokud ne, 
    vrací <tt>false</tt>.</dd>
    
  <dt><tt>+=</tt></dt><dd>pomocí tohoto operátoru se budou přidávat další intervaly do seznamu. Operátor zajistí, 
    že přidané intervaly budou uloženy kompaktně (slučování intervalů). Protože pracujeme s celými čísly, 
    je slučování intervalů poněkud neobvyklé. Je přirozené, že se sloučí překrývající se intervaly, např.: 
    <ul>
     <li><tt>&lt;10..20&gt;</tt> a <tt>&lt;15..30&gt;</tt>,</li>
     <li><tt>&lt;10..30&gt;</tt> a <tt>&lt;15..18&gt;</tt>, případně </li>
     <li><tt>&lt;10..20&gt;</tt> a <tt>&lt;20..30&gt;</tt>,</li>
    </ul> 
    Sloučí se ale i intervaly <tt>&lt;10..20&gt;</tt> a <tt>&lt;21..30&gt;</tt>, přestože se nedotýkají ani nepřekrývají. 
    Dohromady však pokrývají celý interval <tt>&lt;10..30&gt;</tt>. Intervaly <tt>&lt;10..19&gt;</tt> a 
    <tt>&lt;21..30&gt;</tt> se už ale nesloučí, nepokrývají číslo 20.</dd>
    
  <dt><tt>-=</tt></dt><dd>pomocí tohoto operátoru se budou odebírat další intervaly ze seznamu. Odebírání 
    lze chápat i jako množinový rozdíl. Operátor zajistí, že po odebrání budou intervaly uloženy kompaktně 
    (odstraňování nepotřebných intervalů).</dd>
    
  <dt><tt>=</tt></dt><dd>pomocí tohoto operátoru lze nastavit obsah na seznam intervalů na pravé straně 
    (samozřejmě kompaktně uložený).</dd>
    
  <dt><tt>==, !=</tt></dt><dd>operátory porovnají obsah dvou instancí. Za shodné považujeme dvě instance, 
    které mají identický seznam intervalů.</dd>
    
  <dt><tt>&lt;&lt;</tt></dt><dd>operátor zobrazí obsah seznamu do zadaného výstupního streamu. Seznam bude 
    uzavřen ve složených závorkách, jednotlivé intervaly oddělené čárkou. Jednoprvkové intervaly budou 
    zobrazené jako číslo, delší intervaly pak v lomených závorkách. Formát výpisu je zřejmý z ukázek. 
    Intervaly budou zobrazeny seřazené vzestupně.</dd>
</dl>

<p>Úloha nabízí i bonusový test, ve kterém je požadováno další rozhraní pro usnadnění práce se seznamem 
intervalů. Při řešení se můžete rozhodnout, zda budete toto rozšířené rozhraní implementovat (tedy pokusíte 
se o bonus), nebo ne:
<ul>
  <li>pokud rozšířené rozhraní nebudete implementovat, ponechte direktivu preprocesoru 
     <tt>EXTENDED_SYNTAX</tt> v komentáři. Chybějící syntaktické konstrukce se nebudou překládat 
     a bonusový test neudělí body navíc.</li>
  <li>Pokud rozšířenou syntaxi budete implementovat, definujte direktivu preprocesoru 
     <tt>EXTENDED_SYNTAX</tt> (odstraňte komentář). V této situaci pak testovací prostředí bude používat 
     rozšířenou syntaxi a bude hodnotit splnění bonusového testu.</li>
  <li>Pozor, pokud definujte direktivu preprocesoru <tt>EXTENDED_SYNTAX</tt> a potřebné rozhraní nebude 
     implementované, skončí kompilace s chybou.</li>
</ul>
Rozhraní potřebné pro bonusový test syntaxe:</p>
<dl>
  <dt>konstruktor pro inicializaci seznamem hodnot</dt><dd>vyplní instanci zadanými intervaly,</dd>
  <dt>range for loop</dt><dd>instance <tt>CRangeList</tt> musí být použitelná v range for cyklu, kde 
    iterovat přes jednotlivé intervaly ve vzestupném pořadí,</dd>
  <dt>operátor pro výstup musí zobrazovat interval vždy v desítkové podobě, pokud je stream nastaven 
    jinak, musí nastavení streamu upravit a následně obnovit.</dd>
</dl>

<p>Odevzdávejte zdrojový soubor, který obsahuje Vaší implementaci třídy <tt>CRange</tt> a <tt>CRangeList</tt>. 
V odevzdávaném souboru nenechávejte vkládání hlavičkových souborů, Vaše testovací funkce a funkci <tt>main</tt>. 
Pokud v souboru chcete ponechat <tt>main</tt> nebo vkládání hlavičkových souborů, vložte je do bloku 
podmíněného překladu. Využijte přiložený zdrojový kód jako základ Vaší implementace.</p>

<p>V tomto příkladu není poskytnutý přesný předpis pro požadované rozhraní třídy. Z textového popisu, ukázky 
použití v příloze a ze znalostí o přetěžování operátorů byste měli být schopni toto rozhraní vymyslet.</p>

<p>Úloha nabízí bonusové testy, které zkoušejí další vlastnosti Vaší implementace:</p>
<ul>
 <li>První bonusový test dále zkouší, zda implementujete rozhraní pro usnadnění práci se 
   třídou <tt>CRangeList</tt> (viz výše),</li>
   
 <li>Druhý bonus zkouší rychlost operací <tt>includes</tt>, je potřeba rychlejší než 
   lineární řešení.</li>

 <li>Třetí bonus zkouší rychlost operací vkládání a mazání intervalů, je potřeba rychlejší než 
   lineární řešení. Zvládnutí tohoto testu je dost náročné na délku kódu, proto má referenční 
   řešení více řádků než bývá u domácích úloh zvykem (řešení bez tohoto bonusu má rozsah přibližně 
   poloviční).</li>
  
</ul>

<hr />
<b>Nápověda</b><br />
<ul>
 <li>Testovací prostředí kontroluje hodnoty ve Vašich objektech tím, že si je zašle do výstupního proudu 
   a kontroluje jejich textovou podobu. Bez správně fungujícího operátoru pro výstup bude Vaše 
   řešení hodnoceno velmi nízko (téměř 0 bodů).</li>

 <li>Operátor pro výstup implementujte správně -- neposílejte data na <tt>cout</tt>, posílejte je do předaného 
   výstupního proudu. Za výstupem data do proudu nepřidávejte odřádkování ani jiné bílé znaky.</li>

 <li>Pokud Vám program nejde zkompilovat, ujistěte se, že máte správně přetížené operátory. Zejména si 
   zkontrolujte kvalifikátory <tt>const</tt>.</li>
   
 <li>Za zamyšlení stojí operátory += a -=, které musí správně pracovat i se seznamem intervalů na pravé straně. 
   Navíc mezi intervaly na pravé straně lze vkládat operátory + a - (viz ukázka). </li>

 <li>Při implementaci můžete použít <tt>std::vector</tt>, <tt>std::list</tt> a <tt>std::string</tt>. Zbývající kontejnery
   z STL ale nejsou dostupné.</li>
   
 <li>Hranice intervalů jsou zadávané v rozsahu hodnot typu <tt>long long</tt>. V testu mezních hodnot jsou pak zadávané
   i intervaly s počátky a konci <tt>LLONG_MIN</tt> a <tt>LLONG_MAX</tt>.</li>
   
 <li>Nesnažte se používat 128 bitové datové typy. Jejich použití povede k chybě kompilace.</li> 
</ul> 

<p>Správné řešení této úlohy, které splní závazné <b>a bonusové</b> testy na 100%, může být 
odevzdáno k code review. (Tedy pro code review musíte zvládnout i bonusové testy.)</p>
</td> 

</tr>

