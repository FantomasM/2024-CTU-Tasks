<td class="lrtbCell" colspan="3" align="left"><p>Úkolem je vytvořit program, který bude zobrazovat vybrané citáty.</p>

<p>Vstupem programu je jedno celé číslo. Toto číslo je z rozsahu 0 až 8 a 
určuje citát, který má být zobrazen.</p>

<p>Výstupem programu je citát odpovídající zadanému číslu na vstupu. 
Citáty odpovídající jednotlivým číslům jsou uvedené v ukázkových bězích programu níže.
Pozor, za textem citátu je odřádkování (\n).</p>

<p>Pokud je vstup neplatný, program to musí detekovat a zobrazit chybové hlášení.
Chybové hlášení zobrazujte na standardní výstup (ne na chybový výstup). Za chybu považujte:</p>

<ul>
 <li>ze vstupu nelze přečíst celé číslo,</li>
 <li>číslo přečtené ze vstupu je mimo interval 0 až 8.</li>
</ul>

<p>Povšimněte si, že program zobrazuje různá chybová hlášení. První chybové hlášení 
se uplatní, pokud program nemůže ze vstupu přečíst platné celé číslo. Druhé chybové hlášení 
se pak použije, pokud je načtené číslo mimo rozsah (viz ukázka).</p>

<p>Při programování si dejte pozor na přesnou podobu výpisů. Výstup Vašeho programu
kontroluje stroj, který požaduje přesnou shodu výstupů Vašeho programu s výstupy   
referenčními. Za chybu je považováno, pokud se výpis liší. I chybějící nebo přebývající
mezera/odřádkování je považováno za chybu. Abyste tyto problémy rychle vyloučili, 
použijte přiložený archiv se sadou vstupních a očekávaných výstupních dat. Podívejte
se na videotutoriál (courses -&gt; výuková videa), jak testovací data použít a jak 
testování zautomatizovat.</p>

<p>Váš program bude spouštěn v omezeném testovacím prostředí. Je omezen
dobou běhu (limit je vidět v logu referenčního řešení) a dále je omezena i
velikost dostupné paměti (ale tato úloha by ani s jedním omezením neměla mít
problém). Testovací prostředí dále zakazuje používat některé "nebezpečné
funkce" -- funkce pro spouštění programu, pro práci se sítí, ... Pokud jsou
tyto funkce použité, program se nespustí. Možná ve svém programu používáte 
volání:</p>

<pre>
int main ( int argc, char * argv [] )
{
 
  ...
     
  system ( "pause" ); /* aby se nezavrelo okno programu */
  return 0;
}
</pre>

<p>Toto nebude v testovacím prostředí fungovat - je zakázáno spouštění jiného
programu. (I pokud by se program spustil, byl by odmítnut. Nebyl by 
totiž nikdo, kdo by pauzu "odmáčkl", program by čekal věčně a překročil by
tak maximální dobu běhu.) Pokud tedy chcete zachovat pauzu pro testování na
Vašem počítači a zároveň chcete mít jistotu, že program poběží správně,    
použijte následující trik:</p>

<pre>
int main ( int argc, char * argv [] )
{
 
  ...

#ifndef __PROGTEST__
  system ( "pause" ); /* toto progtest "nevidi" */
#endif /* __PROGTEST__ */
  return 0;
} 
</pre>

<b>Ukázka práce programu:</b><br />
<hr />
<pre>
<b>ml' nob:</b>
0
<b>Qapla'</b>
<b>noH QapmeH wo' Qaw'lu'chugh yay chavbe'lu' 'ej wo' choqmeH may' DoHlu'chugh lujbe'lu'.</b>
</pre>
<hr />
<pre>
<b>ml' nob:</b>
1
<b>Qapla'</b>
<b>bortaS bIr jablu'DI' reH QaQqu' nay'.</b>
</pre>
<hr />
<pre>
<b>ml' nob:</b>
2
<b>Qapla'</b>
<b>Qu' buSHa'chugh SuvwI', batlhHa' vangchugh, qoj matlhHa'chugh, pagh ghaH SuvwI''e'.</b>
</pre>
<hr />
<pre>
<b>ml' nob:</b>
3
<b>Qapla'</b>
<b>bISeH'eghlaH'be'chugh latlh Dara'laH'be'.</b>
</pre>
<hr />
<pre>
<b>ml' nob:</b>
4
<b>Qapla'</b>
<b>qaStaHvIS wa' ram loS SaD Hugh SIjlaH qetbogh loD.</b>
</pre>
<hr />
<pre>
<b>ml' nob:</b>
5
<b>Qapla'</b>
<b>Suvlu'taHvIS yapbe' HoS neH.</b>
</pre>
<hr />
<pre>
<b>ml' nob:</b>
6
<b>Qapla'</b>
<b>Ha'DIbaH DaSop 'e' DaHechbe'chugh yIHoHQo'.</b>
</pre>
<hr />
<pre>
<b>ml' nob:</b>
007
<b>Qapla'</b>
<b>Heghlu'meH QaQ jajvam.</b>
</pre>
<hr />
<pre>
<b>ml' nob:</b>
           8
<b>Qapla'</b>
<b>leghlaHchu'be'chugh mIn lo'laHbe' taj jej.</b>
</pre>
<hr />
<pre>
<b>ml' nob:</b>
29
<b>Qih mi' 29</b>
</pre>
<hr />
<pre>
<b>ml' nob:</b>
-5
<b>Qih mi' -5</b>
</pre>
<hr />
<pre>
<b>ml' nob:</b>
abc
<b>Neh mi'</b>
</pre>
<hr />
<b>Poznámky:</b>
<ul>
 <li>Ukázkové běhy zachycují očekávané výpisy Vašeho programu (tučné písmo) a vstupy zadané 
     uživatelem (základní písmo). Zvýraznění tučným písmem je použité pouze zde na stránce zadání, 
     aby byl výpis lépe čitelný. Váš program má za úkol pouze zobrazit text bez zvýrazňování 
     (bez HTML markupu).</li>
     
 <li>Znak odřádkování (\n) je i za poslední řádkou výstupu (i za případným chybovým hlášením).</li>

 <li>Výzvy programu a citáty jsou úmyslně zvoleny tak, aby bylo obtížné je ručně opisovat. Úloha se 
    Vás snaží mj. naučit efektivní práci s počítačem, tedy např. s funkcemi copy &amp; paste (které 
    bohužel někteří studenti neznají nebo neumějí použít). Vyzkoušejte si a naučte se copy &amp; paste 
    jak pod Windows tak pod UNIXem (Linuxem), u závěrečného testu se to bude hodit!</li>

 <li>Ruční kontrola shody Vašeho a referenčního výstupu je nudná, člověk při porovnávání často 
    přehlédne drobný rozdíl. Obzvláště to platí u textu v úloze, který pro většinu lidí není 
    srozumitelný. Toto je opět záměr. Využijte volna na začátku semestru a naučte se v této 
    jednoduché úloze efektivně testovat Vaše programy. Podívejte se na zmíněný videotutoriál 
    (courses -&gt; výuková videa) a využijte pro porovnání Váš počítač. V dalších úlohách tím ušetříte 
    mnoho času.</li>
    
 <li>Vstup typu <code>1.23</code> případně <code>1abcd</code> není správný. Jeho ošetření je ale pracnější. 
    Program proto můžete realizovat v jednodušší podobě, která takový vstup akceptuje jako číslo 1. Takový 
    program bude hodnocen nominálním počtem bodů (100 %). Pro zájemce je k dispozici bonusový test, který 
    zkouší zadávat právě tento typ vstupů. Pokud správně ošetříte i tento typ chyb, bude váš program hodnocen 
    body navíc. Ukázka práce programu pro tento typ vstupu:
<pre>
<b>ml' nob:</b>
1.23
<b>bIjatlh 'e' yImev</b>
</pre></li> 
</ul>

</td> 
