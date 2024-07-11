<td class="header"><b>Dekódování starých textů</b></td>

<td class="lrtbCell" colspan="3" align="left"><meta charset="utf8">

<p>
Při průzkumu na nejodlehlejším místě naší planety byly objeveny pozůstatky dávné civilizace, pečlivě ukryté v temných hlubinách jeskyní.
Mezi těmito vzácnými nálezy jsme narazili na hliněné tabulky s tajemnými texty, jejichž význam zůstává zahalen v mlze.
Co je zvláštní, každá tabulka se zdá být psána jiným jazykem.

<p>
Profesoři z univerzity se ocitli před výzvou: Zjistí jaký jazyk koresponduje s texty na jednotlivých tabulkách?
Aby odhalili tuto záhadu, shromáždili informace o všech možných jazycích, kterými by mohly být texty napsány.
Tyto jazyky formálně popsali pomocí gramatik.

<p>
Pro usnadnění procesu automatického zpracování těchto jazyků navrhli profesoři standardizovaný zápis všech pravidel a převedli gramatiky do této jednotné formy.
Tato reprezentace umožňuje přepsat levou stranu pravidla na dva neterminály nebo jeden terminál.
V případě potřeby generování prázdného slova dovoluje i pravidlo, které přepíše počáteční neterminál na nic, přičemž však počáteční neterminál pak nesmí být obsažen v pravé straně jakéhokoliv pravidla této gramatiky.

<p>
Následující noc byla věnována přepisu symbolů z hliněných tabulek.
K našemu obrovskému potěšení používala tato starodávná civilizace sadu symbolů, která přesně odpovídá symbolům v ASCII kódování, což nám umožnilo snadněji převést symboly do moderní podoby a lehce zpracovávat počítači.

<p>
Na univerzitě však nejsou zdatní programátoři, proto shání pomoc.
Univerzita hledá ty, kdo by byli schopni napsat program, který by rozhodl, zda dané slovo patří do jazyka reprezentovaného gramatikami popsanými výše.
V případě kladné odpovědi je třeba navíc najít způsob, jak může být toto slovo vytvořeno podle pravidel gramatiky.

<p>
Úkol implementujte v podobě funkce programu v C++, jejíž signatura je: <code>std::vector&lt;size_t&gt; trace(const Grammar&, const Word&);</code>.
Vstupem funkce je gramatika jazyka (reprezentována jako struktura <tt>Grammar</tt>) a slovo (<tt>Word</tt>), pro které máte zjistit, zda patří do jazyka.
Tyto struktury jsou definovány v testovacím prostředí, vizte ukázkový soubor.
Gramatika je definována standardně jako v přednáškách.
Pro zjednodušení jsou symboly gramatiky definovány jako jakékoliv hodnoty typu <tt>char</tt>.
Pokud slovo do jazyka patří, pak vraťte nějakou posloupnost indexů pravidel, ze kterých vzniklo postupným derivováním nejlevějšího neterminálu.
Pravidla jsou číslována od nuly.
Pokud slovo do jazyka nepatří, pak je očekáváno, že vrátíte prázdnou posloupnost.

<p>
Je zaručeno, že na vstupu přijde validní gramatika s pravidly podle zadání, tedy:
<ul>
  <li>množiny symbolů (<code>Grammar::m_Terminals</code>, <code>Grammar::m_Nonterminals</code>) nebudou mít průnik,
  <li>veškerá pravidla budou obsahovat pouze symboly z těchto dvou množin,
  <li>všechna pravidla budou mít na pravé straně právě jeden terminál, dva neterminály, nebo, pokud je levou stranou počáteční neterminál, nic (ale pak se ale počáteční neterminál nevyskytuje nikde na pravé straně jiného pravidla),
  <li>počáteční symbol gramatiky se vyskytuje v množině neterminálů a
  <li>mezi pravidly nejsou duplicity.
</ul>

<p>Odevzdávejte zdrojový soubor, který obsahuje implementaci požadované funkce <tt>trace</tt>.
Do zdrojového souboru přidejte i další Vaše podpůrné funkce, které jsou z <tt>trace</tt> volané.
Funkce bude volaná z testovacího prostředí, je proto důležité přesně dodržet zadané rozhraní funkce.
Za základ pro implementaci použijte kód z ukázky níže.
V kódu chybí vyplnit funkci <tt>trace</tt> (a případné další podpůrné funkce).
Ukázka obsahuje testovací funkci <tt>main</tt>, uvedené hodnoty jsou použité při základním testu.
Všimněte si, že vkládání hlavičkových souborů, struktur <code>Grammar</code>, deklarace <code>Word</code> a <code>Symbol</code> a funkce <tt>main</tt> jsou zabalené v bloku podmíněného překladu (<tt>#ifdef/#endif</tt>).
Prosím, ponechte bloky podmíněného překladu i v odevzdávaném zdrojovém souboru.
Podmíněný překlad Vám zjednoduší práci.
Při kompilaci na Vašem počítači můžete program normálně spouštět a testovat.
Při kompilaci na Progtestu funkce <tt>main</tt> a vkládání hlavičkových souborů "zmizí", tedy nebude  kolidovat s hlavičkovými soubory a funkcí <tt>main</tt> testovacího prostředí.</p>

<p>
Pro základ implementace můžete využít soubor ke stažení níže v sekci Vzorová data.

<p>
Váš program bude spouštěn v omezeném testovacím prostředí.
Je omezen dobou běhu (limit je vidět v logu referenčního řešení) a dále je omezena i velikost dostupné paměti.

<p>
V nápovědách má input formát sekvence symbolů oddělených mezerami, tj. <tt>"a b"</tt> je <tt>Word{'a', 'b'}</tt>.</td> 

</tr>
