<td class="header"><b>Determinizace konečného automatu s více počátečními stavy</b></td>

<td class="lrtbCell" colspan="3" align="left"><meta charset="utf8">

<p>
Algoritmus determinizace konečného automatu je klíčovým nástrojem v teorii formálních jazyků.
Nalézá rozsáhlé praktické využití ve zpracování textu, analýze dat a v různých oblastech informatiky.
Tím, že konvertuje nedeterministické automaty na deterministické, umožňuje efektivní analýzu jazyků, což je klíčové v kompilátorech, analýze textu, vyhledávání regulárních výrazů, řízení sítí, databázových systémech a mnoha dalších aplikacích.

<p>
Úkolem je najít deterministický konečný automat <strong>bez zbytečných a nedosažitelných stavů</strong> takový, aby jazyk, který přijímá byl ekvivalentní k jazyku zadaného nedeterministického konečného automatu s více počátečními stavy.

<p>
Determinizaci implementujte v podobě funkce programu v C++, jejíž signatura je: <code>DFA determinize ( const MISNFA & nfa );</code>.
Vstupem, resp. výstupem algoritmu jsou automaty v podobě struktur <code>MISNFA</code>, resp. <code>DFA</code> reprezentující nedeterministický konečný automat s více poč. stavy, resp. deterministický konečný automat.
Tyto struktury jsou definovány v testovacím prostředí, viz ukázka níže.
Pro zjednodušení jsou stavy definovány jako hodnoty typu <tt>int</tt> a symboly abecedy jako hodnoty typu <tt>char</tt>.

<p>
Porovnání automatů s referenčním výsledkem se provádí přes převod na minimální deterministický konečný automat.
Vaše výstupy se mohou lišit (např. v pojmenování stavů).
Po převedení na minimální automat, <strong>které provede testovací prostředí</strong> (tj. minimalizace není vaší starostí), však musí dát ekvivalentní automat (pojmenování stavů nehraje roli).

<p>
Je zaručeno, že na vstupu přijde validní nedeterministický konečný automat s více počátečními stavy, tedy:
<ul>
  <li>množiny stavů (<code>MISNFA::m_States</code>), počátečních stavů (<code>MISNFA::m_InitialStates</code>) a symbolů abecedy (<code>MISNFA::m_Alphabet</code>) budou neprázdné,</li>
  <li>počáteční a koncové stavy z množin <code>MISNFA::m_InitialStates</code> a <code>MISNFA::m_FinalStates</code> budou také prvky množiny stavů <code>MISNFA::m_States</code>,
  <li>pokud nebude pro nějaký stav <tt>q</tt> a symbol abecedy <tt>a</tt> definovaný přechod v automatu, pak v mapě <code>MISNFA::m_Transitions</code> nebude ke klíči <tt>(q, a)</tt> přiřazená hodnota prázdná množina, ale tento klíč nebude vůbec existovat,
  <li>v mapě přechodů <code>MISNFA::m_Transitions</code> se vyskytují také jen prvky, které jsou specifikovány v množině symbolů abecedy a stavů.
</ul>

<p>
Výsledný <tt>DFA</tt> musí také splňovat podmínky definice automatu, tedy musí platit to samé co výše pro MISNFA (až na zřejmé změny kvůli rozdílným definicím počátečního stavu a přechodové funkce).

<p>
V případě, že jazyk automatu je prázdný, odevzdávejte jednostavový automat nad stejnou abecedou, jako je původní automat.

<p>Odevzdávejte zdrojový soubor, který obsahuje implementaci požadované funkce
<tt>determinize</tt>. Do zdrojového souboru přidejte i další Vaše podpůrné funkce, které jsou
z <tt>determinize</tt> volané. Funkce bude volaná z testovacího prostředí, je proto
důležité přesně dodržet zadané rozhraní funkce. Za základ pro implementaci použijte
kód z ukázky níže. V kódu chybí vyplnit funkci <tt>determinize</tt> (a případné další
podpůrné funkce). Ukázka obsahuje testovací funkci <tt>main</tt>, uvedené hodnoty jsou
použité při základním testu. Všimněte si, že vkládání hlavičkových souborů, struktur <code>DFA</code> a <code>MISNFA</code>
a funkce <tt>main</tt> jsou zabalené v bloku podmíněného překladu (<tt>#ifdef/#endif</tt>). Prosím, ponechte
bloky podmíněného překladu i v odevzdávaném zdrojovém souboru. Podmíněný překlad
Vám zjednoduší práci. Při kompilaci na Vašem počítači můžete program normálně
spouštět a testovat. Při kompilaci na Progtestu funkce <tt>main</tt> a vkládání
hlavičkových souborů "zmizí", tedy nebude  kolidovat s hlavičkovými soubory a funkcí
<tt>main</tt> testovacího prostředí.</p>

<p>
Pro základ implementace můžete využít soubor ke stažení níže v sekci Vzorová data.
Tento soubor obsahuje také několik základních testů, mějte však na paměti, že výsledky Vaší ímplementace se mohou lišit.
Testy jsou nastaveny podle výsledků, které dává jedno z referenčních řešení.
Možná si je tedy budete muset upravit.

<p>
Váš program bude spouštěn v omezeném testovacím prostředí.
Je omezen dobou běhu (limit je vidět v logu referenčního řešení) a dále je omezena i velikost dostupné paměti.</td> 

</tr>
