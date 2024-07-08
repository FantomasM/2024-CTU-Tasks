<td class="header"><b>Telefonní seznam</b></td>

<td class="lrtbCell" colspan="3" align="left"><p>Úkolem je vytvořit program, který bude vyhledávat v telefonním seznamu.</p>

<p>Předpokládejme telefonní seznam, kde si ke každému číslu pamatujeme i odpovídající 
jméno. Chceme realizovat program, který v takovém seznamu dokáže efektivně vyhledávat. 
Při vyhledání zadáváme buď  hledané číslo, nebo hledané jméno. Navíc nemusíme jméno ani číslo zadávat celé, 
stačí zadat jeho předponu (prefix). Program prohledá telefonní seznam a vyhledá v něm všechny 
záznamy, které vyhoví zadanému kritériu.</p>

<p>Při zadávání předpokládáme vždy pouze číselné dotazy. Takový číselný dotaz může buď znamenat přímo prefix 
hledaného čísla, nebo se může jednat o jméno zadané pomocí T9 (pro vyhledání záznamů začínajících písmeny <tt>Vagner</tt> 
by byla na vstupu sekvence <tt>824637</tt>).</p>


<p>Vyhledávání bude fungovat interaktivně. Každá řádka vstupu představuje jeden pokyn pro zpracování. Pokynem je buď vložení 
záznamu do telefonního seznamu, nebo vyhledávání. Zadávání pokynů končí po přečtení celého vstupu (dosažení EOF). Pokyny mají podobu:

<ul>
  <li><tt>+ číslo jméno</tt> Tento příkaz přidá záznam do tel. seznamu. Číslo je sekvence znaků 0 až 9, délka čísla je 
    nejméně jedna a nejvýše 20 cifer, pozor, je potřeba správně ukládat i počáteční nuly. Jméno je libovolná sekvence 
    malých a velkých písmen a mezer. Jméno nemůže být prázdné a nesmí začínat ani končit mezerou. Znak +, číslo a jméno 
    na vstupní řádce jsou oddělené právě jednou mezerou.</li>
  
  <li><tt>? číslo</tt> Tento příkaz prohledává telefonní seznam. Číslo je sekvence znaků 0 až 9, délka čísla je nejméně jeden znak 
    (délka není omezená). Znak ? a číslo jsou oddělené právě jednou mezerou.</li>
</ul>

<p>Výstupem programu je vyřešení dotazů. Pro vkládání do seznamu jsou možné 3 odpovědi:</p>
<ul>
 <li>chyba, příkaz není správně formátovaný,</li>
 <li>chyba, do seznamu se vkládá záznam, který v seznamu již existuje (úplná shoda čísla i jména, včetně shody malých a velkých písmen),</li>
 <li>ok, záznam byl vložen do seznamu.</li>
</ul>

<p>Pro vyhledávání jsou možné 3 druhy odpovědi:</p>
<ul>
 <li>chyba, příkaz není správně formátovaný,</li>
 <li>vyhledání záznamů, které odpovídají dotazu, zobrazení vyhledaných záznamů a zobrazení 
   počtu nalezených záznamů. Tento typ odpovědi bude použit, pokud vyhledávaní vyhovuje 
   nejvýše 10 záznamů,</li>
 <li>vyhledání záznamů, které odpovídají dotazu, zobrazení počtu nalezených záznamů. Tato odpověď bude 
   použita, pokud zadanému dotazu vyhovuje více než 10 záznamů v tel. seznamu.</li>
</ul>

<p>Pokud je vstup neplatný, program to musí detekovat a zobrazit chybové hlášení.
Chybové hlášení zobrazujte na standardní výstup (ne na chybový výstup). Po detekování 
chyby program přejde na zpracování další vstupní řádky. Za chybu považujte:</p>

<ul>
 <li>zadaný neznámý příkaz (příkaz musí začínat buď znakem + nebo znakem ?),</li>
 <li>u vkládání chybí číslo nebo jméno,</li>
 <li>u hledání chybí číslo,</li>
 <li>číslo není tvořeno číslicemi,</li>
 <li>jméno není tvořeno znaky abecedy a mezerami,</li>
 <li>jméno začíná nebo končí mezerou,</li>
 <li>chybí nebo přebývají oddělující mezery příkazu/čísla/jména,</li>
 <li>vkládané číslo má více než 20 cifer.</li>
</ul>

<p>Před implementací programu si rozmyslete, jakým způsobem budete telefonní seznam reprezentovat. Počet záznamů 
může být vysoký, délky jmen nejsou shora omezené. Při návrhu se hodí dynamická alokace a struktury.</p>

<p>Vyhledávání může trvat velmi dlouho, zejména pokud je telefonní seznam dlouhý. Časové limity jsou nastavené tak, že 
rozumně implementovaný základní algoritmus vyhledávání projde všemi testy kromě testu bonusového. Bonusový test vyžaduje 
pokročilý algoritmus vyhledávání.</p>


<b>Ukázka práce programu:</b><br />
<hr />

<pre>
+ 123456 Vagner Ladislav
<b>OK</b>
+ 987654321 Vanerka Jiri
<b>OK</b>
+ 824637 Vagner Jiri
<b>OK</b>
+ 8244278 Balik Miroslav
<b>OK</b>
+ 8243245 Vaclavik
<b>OK</b>
+ 192837 Taggart John
<b>OK</b>
+ 98244212 Vogel Josef
<b>OK</b>
? 824
<b>123456 Vagner Ladislav
824637 Vagner Jiri
8244278 Balik Miroslav
8243245 Vaclavik
192837 Taggart John
Celkem: 5</b>
? 82
<b>123456 Vagner Ladislav
987654321 Vanerka Jiri
824637 Vagner Jiri
8244278 Balik Miroslav
8243245 Vaclavik
192837 Taggart John
Celkem: 6</b>
? 37
<b>Celkem: 0</b>
+ 1000001 Vacatko
<b>OK</b>
+ 1000002 Vaclavek
<b>OK</b>
+ 1000003 Vaclavkova
<b>OK</b>
+ 1000006 Vagner Ladislav
<b>OK</b>
+ 1000007 Vacek
<b>OK</b>
+ 1000008 Vachek
<b>OK</b>
+ 1000009 Varga
<b>OK</b>
? 824
<b>123456 Vagner Ladislav
824637 Vagner Jiri
8244278 Balik Miroslav
8243245 Vaclavik
192837 Taggart John
1000006 Vagner Ladislav
Celkem: 6</b>
? 82
<b>Celkem: 13</b>
+ 123456 Novakova
<b>OK</b>
? 123
<b>123456 Vagner Ladislav
123456 Novakova
Celkem: 2</b>
? 123456
<b>123456 Vagner Ladislav
123456 Novakova
Celkem: 2</b>
? 1234567
<b>Celkem: 0</b>
? 10000
<b>1000001 Vacatko
1000002 Vaclavek
1000003 Vaclavkova
1000006 Vagner Ladislav
1000007 Vacek
1000008 Vachek
1000009 Varga
Celkem: 7</b>
+ 123456 Novakova Jana
<b>OK</b>
+ 234567 Novakova Jana
<b>OK</b>
+ 123456 Novakova Jana
<b>Kontakt jiz existuje.</b>
+ 123456 Novakova Jana
<b>Kontakt jiz existuje.</b>
+ 123456 novakova Jana
<b>OK</b>
? 123456
<b>123456 Vagner Ladislav
123456 Novakova
123456 Novakova Jana
123456 novakova Jana
Celkem: 4</b>
</pre>

<hr />

<pre>
+ 123456 test
<b>OK</b>
+ 1234567 test
<b>OK</b>
+ 123456 testtest
<b>OK</b>
+ 123456 test
<b>Kontakt jiz existuje.</b>
+ 123456    test
<b>Nespravny vstup.</b>
+ 123456789012345678901234567890 foo
<b>Nespravny vstup.</b>
? test
<b>Nespravny vstup.</b>
?
<b>Nespravny vstup.</b>
test
<b>Nespravny vstup.</b>
</pre>

<hr />

<b>Poznámky:</b>
<ul>
<li>V ukázkovém běhu programu jsou vizuálně odlišené uživatelské vstupy (standardní font) a výpisy 
   programu (tučné písmo). Toto rozlišení je použité pouze zde na WWW stránce zadání problému, aby se 
   výpis snáze četl. Realizovaný program musí zobrazovat text bez dalších úprav (nepoužívá žádný markup), 
   viz též přiložené soubory.</li>

<li>Znak odřádkování (\n) je i za poslední řádkou výstupu (i za případným chybovým hlášením).</li>

<li>Pro reprezentaci tel. čísel nepoužívejte datový typ <tt>int</tt>.</li>

<li>Program nelze vytvořit bez dynamické alokace paměti.</li>

<li>V programu používejte prostředky jazyka C, nepoužívejte C++ (STL).</li>
 
<li>Při načítání dat ze vstupu je potřeba rozumně efektivní implementace. Pokud byste potřebovali 
   zvětšovat velikost nějakého dynamicky alokovaného pole, nezvětšujte jej po jednotlivých prvcích.</li>

<li>Vyplatí se načítat jednotlivé řádky na vstupu a zpracovávat je jako řetězce v paměti.</li>

<li><a href="https://cs.wikipedia.org/wiki/T9">T9 kódování</a> (malá i velká písmena):
<pre>
   ABC    2
   DEF    3
   GHI    4
   JKL    5
   MNO    6
   PQRS   7
   TUV    8
   WXYZ   9
   mezera 1   
</pre></li>

<li>Pořadí nalezených kontaktů v odpovědi programu není důležité. Testovací prostředí si 
  pořadí odpovědí před porovnáním upraví.</li>
<li>Řešení této úlohy, které projde všemi závaznými a nepovinnými testy na 100%, může být použito 
   pro code review (pro code review není požadované zvládnutí testu rychlosti).</li>
</ul>
</td> 

</tr>
