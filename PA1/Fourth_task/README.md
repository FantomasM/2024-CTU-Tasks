<td class="header"><b>Finanční analýza</b></td>

<td class="lrtbCell" colspan="3" align="left"><p>Úkolem je vytvořit program, který bude filtrovat finanční data, aby "lépe vypadala".</p>

<p>Předpokládáme, že máme informace o stavu účtu v čase. Z těchto dat je potřeba vybrat vhodný 
úsek do prezentace. V prezentaci chceme dokumentovat dobré hospodaření s prostředky 
v dlouhodobém horizontu. Tedy chceme vybrat co nejdelší spojitý úsek dat (to je primární kritérium), 
ale zároveň požadujeme, aby stav účtu na konci vybraného úseku byl vyšší nebo roven stavu účtu na 
začátku vybraného úseku dat. Fakticky nás tedy zajímá pouze hodnota na začátku a na konci vybraného 
úseku dat, hodnoty uvnitř vybraného úseku dat nejsou důležité, při výběru nehrají žádnou roli.</p>

<p>Pokud je na vstupu posloupnost hodnot např.: <tt>115 111 57 56 103 96 -1000 100 83 45</tt>, bude 
výsledkem úsek od hodnoty <tt>57</tt> do hodnoty <tt>83</tt> (je nejdelší možný a 83 &ge; 57).</p>

<p>Vstupem programu je posloupnost celých čísel, která udává stav účtu v čase. Délka posloupnosti 
je omezena nejvýše na 250000 hodnot. Zadávání hodnot končí v okamžiku, kdy je detekován EOF (konec vstupu).</p>

<p>Výstupem programu je nalezený úsek maximální délky takový, že stav účtu na konci úseku 
je vyšší nebo rovný stavu účtu na začátku úseku. Program zobrazí délku úseku a indexy 
začátku a konce (indexy počítané od 0). Stejně dlouhých úseků může existovat více než 
jeden, pak program v libovolném pořadí zobrazí všechny možnosti. Může se stát, že vstupní 
posloupnost neobsahuje žádný vhodný úsek, v tomto případě je zobrazeno speciální hlášení (viz ukázka).</p>

<p>Pokud je vstup neplatný, program to musí detekovat a zobrazit chybové hlášení.
Chybové hlášení zobrazujte na standardní výstup (ne na chybový výstup). Za chybu považujte:</p>

<ul>
 <li>vstup není celé číslo,</li>
 <li>na vstupu nejsou alespoň dvě hodnoty,</li>
 <li>vstup je delší než 250000 hodnot.</li>
</ul>

<b>Ukázka práce programu:</b><br />

<hr />

<pre>
<b>Hodnoty:</b>
115 111 57 56 103 96 -1000 100 83 45
<b>7: 2 - 8</b>
<b>Moznosti: 1</b>
</pre>
<hr />
<pre>
<b>Hodnoty:</b>
5 9 11 8 
   4 16 -8 


3 1 3
<b>6: 0 - 5</b>
<b>Moznosti: 1</b>
</pre>
<hr />
<pre>
<b>Hodnoty:</b>
23 112 5 11 8 4 16 -8 3 0 1 3
<b>5: 7 - 11</b>
<b>5: 2 - 6</b>
<b>Moznosti: 2</b>
</pre>
<hr />
<pre>
<b>Hodnoty:</b>
9 7 3 1 -8 -1000
<b>Nelze najit.</b>
</pre>
<hr />
<pre>
<b>Hodnoty:</b>
1 2 3 4 hello
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

 <li>Pro reprezentaci hodnot postačuje datový typ <tt>int</tt>.</li>

 <li>Vstupní hodnoty je potřeba ukládat do pole, výsledek nelze určit on-line. Vstupní posloupnost 
     má délku nejvýše 250000, postačuje tedy staticky alokované pole s touto velikostí. Nealokujte 
     pole dynamicky, zbytečně si tím úlohu zkomplikujete.</li>
     
 <li>Úloha nabízí bonus, kterého lze dosáhnout, pokud je řešení časově efektivní. Časové efektivity lze 
     dosáhnout zejména tím, že zvolíte vhodný algoritmus zpracování a rozumně efektivně jej implementujete:
     <ul>
       <li>Test rychlosti 1 lze zvládnout naivním (kvadratickým) algoritmem, pokud zvolíte vhodnou 
         implementaci. Pokud Vaše implementace tímto testem neprojde, nedosáhnete plných 100% bodů.</li>
       <li>Test rychlosti 2 lze zvládnout pouze pokud je použitý algoritmus efektivnější než kvadratický. 
         Pokud tento test zvládnete, získáte hodnocení vyšší než 100%.</li>
</ul></li>
     
<li>Pokud má úloha více řešení, musí je program zobrazit všechna. Jejich pořadí ve výpisu ale není 
    podstatné, testovací prostředí si pořadí nalezených úseků před porovnáním uspořádá.</li>
</ul>
</td> 

</tr>


<tr>
<td class="ltbCell" colspan="2" align="left"><b>Vzorová data:</b></td>
<td class="rtbCell" align="center"><div class="but1 w120"><div class="but2"><a class="butLink" href="?X=TaskS&amp;Cou=395&amp;Tgr=2530&amp;Tsk=1490">Download</a></div></div></td>
</tr>
