<td class="header"><b>Řídká matice</b></td>

<td class="lrtbCell" colspan="3" align="left"><p>Úkolem je realizovat sadu funkcí pro práci s řídkými maticemi.
Řídká matice je taková matice, která má nastaveno pouze málo hodnot
(např. pouze 1 %) a ostatní hodnoty nejsou nastavené (nenastavené
hodnoty jsou typicky považované za 0). Proto se ji vyplatí ukládat
jinak než 2D polem. Naše řídká matice bude realizovaná pomocí
spojových seznamů.</p>

<p>Vlastní matice je realizovaná strukturou <tt>TSPARSEMATRIX</tt>. V této struktuře
jsou odkazy na dva jednosměrně zřetězené spojové seznamy existujících (neprázdných)
řádek a sloupců. Spojový seznam řádek (sloupců) je realizován pomocí struktur <tt>TROWCOL</tt>.
Prvkem spojového seznamu je popis řádky matice (sloupce matice), ve kterém je
alespoň jeden obsazený prvek. Řádky (sloupce) v seznamu jsou uspořádané podle rostoucího indexu.
Ve struktuře <tt>TROWCOL</tt> je pak ukazatel <tt>m_Cells</tt> na jednotlivé prvky
obsažené v dané řádce (sloupci).</p>

<p>Struktura <tt>TCELL</tt> popisuje jeden prvek matice. Obsahuje pozici (řádek, sloupec),
hodnotu a dva ukazatele na další prvky: další prvek na řádce a další prvek ve sloupci. Prvky
v řádcích (sloupcích) jsou uspořádané vzestupně podle svých sloupcových (řádkových) indexů.
Následující obrázek zachycuje řídkou matici, ve které byly zadané prvky:</p>
<pre>
m[0, 1] = 10
m[1, 0] = 20
m[1, 5] = 30
m[2, 1] = 40
</pre>

<center><img src="https://imgur.com/a/taBvfJw" /></center>

<hr />

<dl>
 <dt><tt>TSPARSEMATRIX</tt></dt>
 <dd>tato datová struktura je deklarovaná v testovacím prostředí. Vaše implementace
   bude s touto strukturou pracovat, ale nesmí jí nijak měnit. Struktura reprezentuje
   celou matici, má následující složky:
   <ul>
     <li><tt>m_Rows</tt> - ukazatel na počátek spojového seznamu existujících řádek matice,</li>
     <li><tt>m_Cols</tt> - ukazatel na počátek spojového seznamu existujících sloupců matice.</li>
   </ul><dd>

 <dt><tt>TROWCOL</tt></dt>
 <dd>tato datová struktura je deklarovaná v testovacím prostředí. Vaše implementace
   bude s touto strukturou pracovat, ale nesmí jí nijak měnit. Struktura reprezentuje
   spojový seznam popisující existující řádek nebo sloupec matice, má následující složky:
   <ul>
     <li><tt>m_Next</tt> - ukazatel na další řádek/sloupec matice, <tt>nullptr</tt> pro poslední existující řádek (sloupec),</li>
     <li><tt>m_Idx</tt> - index řádku (sloupce),</li>
     <li><tt>m_Cells</tt> - ukazatel na počátek spojového seznamu prvků matice, které patří do popisovaného řádku (sloupce). Protože
       ve spojovém seznamu máme pouze existující řádky (sloupce) matice, nebude hodnota <tt>m_Cells</tt> nikdy rovná <tt>nullptr</tt>.</li>
   </ul><dd>

 <dt><tt>TCELL</tt></dt>
 <dd>tato datová struktura je deklarovaná v testovacím prostředí. Vaše implementace
   bude s touto strukturou pracovat, ale nesmí jí nijak měnit. Struktura reprezentuje
   jeden prvek matice, má následující složky:
   <ul>
     <li><tt>m_Right</tt> - ukazatel na další prvek matice ve stejném řádku (a vyšším sloupci), <tt>nullptr</tt> pro poslední prvek na řádce,</li>
     <li><tt>m_Down</tt> - ukazatel na další prvek matice ve stejném sloupci (a vyšším řádku), <tt>nullptr</tt> pro poslední prvek ve sloupci,</li>
     <li><tt>m_Row</tt> - index řádku,</li>
     <li><tt>m_Col</tt> - index sloupce,</li>
     <li><tt>m_Data</tt> - hodnota prvku matice.</li>
   </ul><dd>


 <dt><tt>initMatrix ( m )</tt></dt>
 <dd>funkce inicializuje prázdnou matici - efektivně nastaví spojové seznamy řádek a sloupců na hodnoty <tt>nullptr</tt>.</dd>

 <dt><tt>addSetCell ( m, row, col, value )</tt></dt>
 <dd>funkce přidá do matice prvek na zadané řádce a
    sloupci (<tt>row</tt>, <tt>col</tt>) a vyplní jej hodnotou <tt>value</tt>. Pokud prvek
    již v matici existoval, pouze nastaví jeho novou hodnotu. Pokud prvek na pozici <tt>row</tt>, <tt>col</tt>
    ještě neexistoval, funkce jej vytvoří, vyplní a správně začlení do spojových seznamů.</dd>

 <dt><tt>removeCell ( m, row, col )</tt></dt>
 <dd>funkce odstraní z matice  prvek na zadané řádce a sloupci (<tt>row</tt>, <tt>col</tt>). Pokud
    prvek v matici neexistoval, funkce vrátí <tt>false</tt> a nechá matici beze změny. Pokud prvek
    existoval, funkce jej z matice odstraní, upraví odpovídající spojové seznamy a vrátí <tt>true</tt>.
    Pozor, pokud odstraňujete poslední prvek na řádce (ve sloupci), je potřeba upravit i spojové
    seznamy existujících řádků (sloupců).</dd>

 <dt><tt>freeMatrix ( m )</tt></dt>
 <dd>funkce k uvolnění prostředků alokovaných v matici.</dd>

</dl>

<p>Odevzdávejte zdrojový soubor, který obsahuje implementaci požadovaných funkcí. Do
zdrojového souboru přidejte i další Vaše podpůrné funkce, které jsou z nich volané.
Implementované funkce budou volané z testovacího prostředí, je proto důležité přesně
dodržet zadané rozhraní funkcí. Za základ pro implementaci použijte kód z přiloženého
souboru. V kódu chybí vyplnit těla požadovaných funkcí (a případné další podpůrné funkce). Ukázka
obsahuje testovací funkci <tt>main</tt>, uvedené hodnoty jsou použité při
základním testu. Všimněte si, že vkládání hlavičkových souborů a funkce
<tt>main</tt> jsou zabalené v bloku podmíněného překladu (<tt>#ifdef/#endif</tt>). Prosím, ponechte
bloky podmíněného překladu i v odevzdávaném zdrojovém souboru. Podmíněný překlad
Vám zjednoduší práci. Při kompilaci na Vašem počítači můžete program normálně
spouštět a testovat. Při kompilaci na Progtestu funkce <tt>main</tt> a vkládání
hlavičkových souborů "zmizí", tedy nebude  kolidovat s hlavičkovými soubory a funkcí
<tt>main</tt> testovacího prostředí.</p>


<p>Váš program bude spouštěn v omezeném testovacím prostředí. Je omezen
dobou běhu (limit je vidět v logu referenčního řešení) a dále je omezena i
velikost dostupné paměti. Rozumná implementace naivního algoritmu by měla
projít všemi testy.</p>

<hr />
<b>Nápověda:</b><br />
<ul>
 <li>Jako základ Vašeho řešení použijte zdrojový kód z přiloženého souboru.</li>

 <li>Do funkce <tt>main</tt> si můžete doplnit i
  další Vaše testy, případně ji můžete libovolně změnit.
  Důležité je zachovat podmíněný překlad.</li>

 <li>V ukázce je použito makro <tt>assert</tt>. Pokud je parametrem
  nenulová hodnota, makro nedělá nic. Pokud je parametrem nepravda (nula),
  makro ukončí program a vypíše řádku, kde k selhání došlo. Pokud tedy
  Vaše implementace projde ukázkovými testy, program doběhne a nic nezobrazí.</li>

 <li>Řešení této úlohy nelze použít pro code review.</li>
</ul>
</td> 

</tr>
