<td class="header"><b>SETI</b></td>
<tr>

        <td class="lrtbCell" colspan="3" align="left"><p>Úkolem je vytvořit program, který bude analyzovat vysílání mimozemských civilizací.</p>

<p>Radioastronomům se podařilo zachytit zprávy mimozemských civilizací. Konečně. Zprávy přicházejí 
od hvězd, které mají podobné charakteristiky, jako Slunce. Není pochyb.</p>

<p>Problém je zprávy dekódovat. Překvapivě, kódování všech zpráv je stejné (mimozemský 
UNICODE), navíc, od jedné hvězdy přichází ta samá zpráva stále dokola. Jednou z otázek 
je, zda se zprávy někdy sesynchronizují, tedy, zda v nějakém okamžiku budeme přijímat 
všechny zprávy od jejich začátku.</p>

<p>Vstupem programu jsou dvě nebo více zpráv. Každá zpráva je zadaná na jedné řádce jako posloupnost písmen 
malé abecedy. Každé písmeno určuje délku zachyceného pulzu: a=1, b=2, c=4, d=8, e=16, ... 
Dále je na vstupu znak |, který určuje začátek zprávy. Tedy vstup v podobě:

<pre>
ea|babab
</pre>

<p>představuje zprávu s pulzy délky 16, 1, 2, 1, 2, 1 a 2. Celková délka zprávy je 
16 + 1 + 2 + 1 + 2 + 1 + 2=25 časových jednotek. Zpráva je zaznamenaná tak, že do 
jejího konce zbývá ještě 16+1=17 časových jednotek.</p>

<p>Program takto dostane na svém vstupu několik zpráv, každá zpráva může mít různou délku 
a aktuální pozice v každé zprávě také může být jiná. Program určí, zda dojde k synchronizaci 
ve všech zprávách a kdy k tomu dojde. Například pro vstup:</p>
<pre>
ea|babab
d|abaca
</pre>
dojde k synchronizaci za 42 jednotek času:
<pre>
ea|  bababea|          = 42
d|   abacad|abacad|    = 42
</pre>

<p>Vstupem programu jsou přijímané zprávy ve formátu popsaném výše. Zprávy jsou nejméně dvě. 
Pro základní testy jsou na vstupu pouze dvě zprávy, bonusové testy zadávají více 
zpráv na vstupu.</p>

<p>Výstupem programu je vypočtená informace, kdy se vstupní zprávy sesynchronizují. Pro některé
vstupy se může stát, že se zprávy nikdy nesesynchronizují, v této situaci je zobrazena 
jiná odpověď (viz ukázky).</p>

<p>Pokud je vstup neplatný, program to musí detekovat a zobrazit chybové hlášení.
Chybové hlášení zobrazujte na standardní výstup (ne na chybový výstup). Za chybu považujte:</p>

<ul>
 <li>méně než dvě vstupní zprávy,</li>
 <li>zpráva nemá správný formát (nesmí být prázdná, musí obsahovat pouze písmena malé abecedy a 
    právě jeden znak kolmítko).</li>
</ul>

<b>Ukázka práce programu:</b><br />
<hr />
<pre>
<b>Zpravy:</b>
ea|babab
d|abaca
<b>Synchronizace za: 42</b>
</pre>
<hr />
<pre>
<b>Zpravy:</b>
acacbbaaa|
cbbcabcbbaa|
<b>Synchronizace za: 0</b>
</pre>
<hr />
<pre>
<b>Zpravy:</b>
|acabbaaa
|dcbabaaaa
<b>Synchronizace za: 0</b>
</pre>
<hr />
<pre>
<b>Zpravy:</b>
acacbbaa|baa
bcaabaa|baaa
<b>Synchronizace za: 216</b>
</pre>
<hr />
<pre>
<b>Zpravy:</b>
cbbcbaa|aaaa
aadaaaabaaa|abaa
<b>Nelze dosahnout.</b>
</pre>
<hr />
<pre>
<b>Zpravy:</b>
dbdccdccbbbbaa|aaaa
bebbaedbcabbaa|ccbaa
<b>Synchronizace za: 276</b>
</pre>
<hr />
<pre>
<b>Zpravy:</b>
jfddiaggfdffaagfacafcfbbbgdcddbfaedfeaacfeadcbabbaaa|hdccdfdbfadcdbbcbbaa
bhfdigdbggfadfdddacceaedbefeacbacaacbbbaa|cdcgebfichfbgcbjbhdfadgheifheceeehiceeedfbgcgaggfdaadacbdeccbaadbbabaa
<b>Synchronizace za: 5046543</b>
</pre>
<hr />
<pre>
<b>Zpravy:</b>
acacbb|aaa
cbbcabcbbaa
<b>Nespravny vstup.</b>
</pre>
<hr />
<pre>
<b>Zpravy:</b>
acacbb|aaa
cbbc abcb|baa
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

 <li>Úlohu lze vyřešit bez použití funkcí. Pokud ale správně použijete funkce, 
    bude program přehlednější a bude se snáze ladit.</li>

 <li>Není potřeba alokovat pole. Práce s polem úlohu zbytečně zkomplikuje. Vstupy lze načítat průběžně 
   a ukládat si pouze agregované hodnoty.</li>
   
 <li>Pro načítání vstupu se hodí funkce <tt>scanf</tt> s formátem <tt>%c</tt> nebo funkce <tt>fgetc</tt>.</li>  
    
 <li>Hodnocení připouští různě dokonalá řešení, podle úrovně řešení budou přidělené body navíc:
  <ul>
   <li>první bonus získá řešení, které dokáže pracovat s více než dvojicí zpráv na vstupu,</li>
 
   <li>druhý bonus získá řešení, které použije efektivní algoritmus výpočtu, a dokáže rychle pracovat 
     i pro dlouhé zprávy,</li>
 
   <li>třetí bonus získá řešení, které použije efektivní algoritmus výpočtu, a dokáže rychle pracovat 
     i pro velmi dlouhé zprávy.</li>
  </ul>
 </li>
   
 <li>Pro výpočty v základních testech stačí datový typ <tt>int</tt>. Pro zvládnutí druhého a třetího bonusu je potřeba 
   pracovat s velkými čísly, která překračují rozsah typu <tt>int</tt>. Doporučený je datový typ <tt>long int</tt>
   nebo <tt>long long int</tt>. Pro zvládnutí třetího bonusu (a s některými algoritmy i pro druhý bonus) budete 
   dokonce muset ukládat mezivýsledky v typu <tt>__int128_t</tt> (tento typ je nestandardní, má rozsah 128 bitů, 
   neexistuje pro něj standardní vstupní a výstupní konverze, ale lze jej použít v aritmetických operacích).</li>
</ul>


</td> 

       </tr>
