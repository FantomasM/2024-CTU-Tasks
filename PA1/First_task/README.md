 <h1>Přestupy na nádraží</h1>
 <td class="lrtbCell" colspan="3" align="left"><p>Úkolem je realizovat program, který bude rozhodovat o možnostech 
přestupu mezi vlaky na nádraží.</p>

<p>Předpokládáme, že na nádraží jezdí za den
právě 3 vlaky - vlak A, B a C. Vlaky jezdí denně, přijíždějí a odjíždějí 
vždy ve stejný čas. Pro každý vlak známe hodinu a minutu příjezdu a odjezdu. 
Úkolem programu je rozhodnout, mezi kterými vlaky lze přestoupit. 
Z vlaku X lze přestoupit do vlaku Y pokud vlak Y odjíždí alespoň 5 minut po
příjezdu vlaku X (5 minut je na přestup). Dále, přestoupit můžeme pouze
tehdy, pokud od příjezdu X do příjezdu Y jsou nejvýše 3 hodiny včetně. 
Pokud by vlak Y přijel později, zdrželi bychom se na nástupišti déle než 
3 hodiny a byli bychom z nádraží vykázáni jako potenciální bezdomovci.
Oba limity (5 min, 3h) jsou brané včetně, je to i demonstrováno v ukázkách
níže.</p>

<p>Vstupem programu je 6 časových údajů o příjezdech a odjezdech vlaků,
každý údaj je tvořen hodinou a minutou. Hodiny a minuty jsou oddělené
dvojtečkou.</p>

<p>Výstupem programu je rozhodnutí, mezi kterými vlaky lze přestupovat. 
Odpovědi jsou postupně pro vlaky A, B a C, každá na zvláštním řádku. Formát
výstupu je zřejmý z ukázek níže. Pokud lze přestupovat na více vlaků, jsou
vlaky, na které lze přestoupit, uvedeny abecedně:
<pre>
Z vlaku B lze prestoupit na vlaky A a C.
</pre>
Naopak, následující odpověď by byla vyhodnocena jako nesprávná:
<pre>
Z vlaku B lze prestoupit na vlaky C a A.
</pre>
Nezapomeňte na odřádkování za každou (tedy i poslední) řádkou výpisu.</p>

<p>Pokud vstup není platný (na vstupu jsou nečíselné nebo nesmyslné
hodnoty), program tuto situaci detekuje a vypíše chybové hlášení. Formát
chybového hlášení je opět uveden v ukázkách níže. Za chybu je považováno,
pokud je na vstupu:</p>
<ul>
 <li>nečíselná hodnota,</li>
 <li>chybějící oddělovač (dvojtečka) nebo</li>
 <li>nesmyslná hodnota (hodnota mimo rozsah 0-23, resp. 0-59).</li>
</ul>
 
<p>Pokud program detekuje chybu, přestane se dotazovat na další vstupní
hodnoty, vypíše chybové hlášení a ukončí se. Chybu je tedy potřeba 
detekovat okamžitě po načtení hodnoty (neodkládejte kontrolu vstupních 
údajů až za načtení celého vstupu). Chybové hlášení vypisujte na standardní
výstup (nevypisujte jej na standardní chybový výstup).</p>

<p>Dodržte přesně formát všech výpisů. Výpis Vašeho programu musí přesně
odpovídat ukázkám. Testování provádí stroj, který kontroluje výpis na
přesnou shodu. Pokud se výpis Vašeho programu liší od referenčního výstupu,
je Vaše odpověď považovaná za nesprávnou. Záleží i na mezerách, i na
odřádkování. Nezapomeňte na odřádkování za posledním řádkem výstupu (a za
případným chybovým hlášením). Využijte přiložený archiv s testovacími vstupy
a usnadněte si testování Vašeho programu.</p>

<p>Váš program bude spouštěn v omezeném testovacím prostředí. Je omezen
dobou běhu (limit je vidět v logu referenčního řešení) a dále je omezena i
velikost dostupné paměti (ale tato úloha by ani s jedním omezením neměla mít
problém).</p>

<b>Ukázka práce programu:</b><br />

<hr />
<pre>
<b>Cas prijezdu vlaku A:</b>
12:00
<b>Cas odjezdu vlaku A:</b>
12:30
<b>Cas prijezdu vlaku B:</b>
12:10
<b>Cas odjezdu vlaku B:</b>
12:20
<b>Cas prijezdu vlaku C:</b>
12:40
<b>Cas odjezdu vlaku C:</b>
13:00
<b>Z vlaku A lze prestoupit na vlaky B a C.</b>
<b>Z vlaku B lze prestoupit na vlaky A a C.</b>
<b>Z vlaku C nelze prestupovat.</b>
</pre>
<hr />
<pre>
<b>Cas prijezdu vlaku A:</b>
10:00
<b>Cas odjezdu vlaku A:</b>
10:10
<b>Cas prijezdu vlaku B:</b>
10:05
<b>Cas odjezdu vlaku B:</b>
10:15
<b>Cas prijezdu vlaku C:</b>
10:06
<b>Cas odjezdu vlaku C:</b>
10:16
<b>Z vlaku A lze prestoupit na vlaky B a C.</b>
<b>Z vlaku B lze prestoupit na vlaky A a C.</b>
<b>Z vlaku C lze prestoupit na vlak B.</b>
</pre>
<hr />
<pre>
<b>Cas prijezdu vlaku A:</b>
10:00
<b>Cas odjezdu vlaku A:</b>
10:30
<b>Cas prijezdu vlaku B:</b>
13:00
<b>Cas odjezdu vlaku B:</b>
13:10
<b>Cas prijezdu vlaku C:</b>
13:01
<b>Cas odjezdu vlaku C:</b>
14:00
<b>Z vlaku A lze prestoupit na vlak B.</b>
<b>Z vlaku B lze prestoupit na vlak C.</b>
<b>Z vlaku C lze prestoupit na vlak B.</b>
</pre>
<hr />
<pre>
<b>Cas prijezdu vlaku A:</b>
23:00
<b>Cas odjezdu vlaku A:</b>
23:30
<b>Cas prijezdu vlaku B:</b>
23:50
<b>Cas odjezdu vlaku B:</b>
0:15
<b>Cas prijezdu vlaku C:</b>
0:10
<b>Cas odjezdu vlaku C:</b>
0:45
<b>Z vlaku A lze prestoupit na vlaky B a C.</b>
<b>Z vlaku B lze prestoupit na vlak C.</b>
<b>Z vlaku C lze prestoupit na vlak B.</b>
</pre>
<hr />
<pre>
<b>Cas prijezdu vlaku A:</b>
12:00
<b>Cas odjezdu vlaku A:</b>
12:65
<b>Nespravny vstup.</b>
</pre>
<hr />
<pre>
<b>Cas prijezdu vlaku A:</b>
12:00
<b>Cas odjezdu vlaku A:</b>
12:abc
<b>Nespravny vstup.</b>
</pre>

<hr />
<b>Poznámky:</b>
<ul>
 <li>Ukázkové běhy zachycují očekávané výpisy Vašeho programu (tučné písmo) a vstupy zadané 
     uživatelem (základní písmo). Zvýraznění tučným písmem je použité pouze zde na stránce zadání, 
     aby byl výpis lépe čitelný. Váš program má za úkol pouze zobrazit text bez zvýrazňování 
     (bez HTML markupu).</li>
     
 <li>Znak odřádkování (\n) je i za poslední řádkou výstupu (i za případným chybovým hlášením).</li>
</ul>
</td> 

