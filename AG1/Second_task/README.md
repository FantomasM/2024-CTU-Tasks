<td class="header"><b>Textový editor</b></td>

<td class="lrtbCell" colspan="3" align="left"><p>Před dávnými časy, v předaleké galaxii, žily na planetě Zemi dva
naprosto nesmiřitelné kmeny uživatelů. Každý z kmenů uctíval jako svého
boha jeden ze dvou velice mocných textových editorů: Vim a Emacs. Jednou
z nejdůležitějších životních náplní (a zlí jazykové tvrdí, že pro
některé to byla náplň jediná) těchto uživatelů bylo vést vášnivé
internetové diskuze o tom, který z editorů je lepší. Každý z nich
tvrdil, že jeho editor je ten nejlepší a že ten druhý by měl být pro
nízkou efektivitu zakázán příslušnými úřady.</p>
<p>Avšak v jednom malém koutě této planety se narodil mladý a nadějný
programátor jménem Elon, jehož myšlenky byly jiné než ostatních. Vnímal
nesmiřitelný boj mezi Vimem a Emacsem jako ztrátu času a energie. Byl
přesvědčen, že by bylo mnohem lepší, kdyby se spojily nejlepší
vlastnosti obou editorů do jednoho všestranného nástroje.</p>
<p>Tak Elon začal pracovat na projektu, který měl přinést jednotu mezi
uživatel Vimu a Emacsu. Rozhodl se tedy vytvořit úžasný textový editor,
který bude kombinovat sílu Vimových zkratek s flexibilitou Emacsových
rozšíření. Ale to nebylo vše. Elon chtěl, aby jeho editor byl tak
revoluční, že by nadchl nejen pokročilé uživatele textových editorů, ale
celou planetu, včetně tzv. BFU. Proto se rozhodl, že spojí ještě dvě
důležité vlastnosti každého z editorů: z prostředí Emacsu zakomponuje
poučku „dobrý operační systém, ale špatný editor“, z Vimu pak do nového
editoru přenese nemožnost editor vypnout.</p>
<p>Elon, který si liboval v efektivitě, se rozhodl svůj editor
pojmenovat χ. Právě χ se měl stát symbolem spojení, pokroku, svobody a
míru na celé Zemi. A od té doby žili programátoři v harmonii, každý mohl
používat χ podle svého gusta a nikdo už se nezabýval hádkami mezi Vimem
a Emacsem. Byli šťastní a tvořili spolu úžasné programy a projekty,
protože χ jim umožňoval dosáhnout maxima jejich tvůrčí síly.</p>
<p><br></p>
<p>Opravdu věříš, že by se něco takové mohlo stát? Kdepak, to je jenom
pohádka. Elon ve skutečnosti sám moc programovat neumí, je dobrý spíše v
impulzivním rozhodování, krizovém managementu a marketingu. Požádal tě
proto, zda bys mu s programováním editoru nepomohl. Výměnou za tvých 120
hodin práce týdně ti slibuje, že až χ vypustí do světa, budeš uveden v
seznamu autorů hned na druhém místě.</p>
<h2 id="rozhraní-programu">Rozhraní programu</h2>
<p>Vaším úkolem je implementovat třídu <code>TextEditorBackend</code>,
která představuje backend textového editoru. Požadované rozhraní:</p>
<ul>
<li><p><code>TextEditorBackend(const std::string&amp; text)</code>:
konstruktor, který inicializuje obsah editoru daným textem.</p></li>
<li><p><code>size_t size() const</code>: Počet znaků textu včetně nových
řádků.</p></li>
<li><p><code>size_t lines() const</code>: Počet řádků. Prázdný text má
jeden řádek. Každý znak <code>\n</code> přidá řádek.</p></li>
<li><p><code>char at(size_t i) const</code>: Vrátí <code>i</code>-tý
znak. Povolený rozsah je <code>[0, size())</code>.</p></li>
<li><p><code>void edit(size_t i, char c)</code>: Nahradí znak na pozici
<code>i</code> znakem <code>c</code>. Povolený rozsah je
<code>[0, size())</code>.</p></li>
<li><p><code>void insert(size_t i, char c)</code>: Vloží znak
<code>c</code> před znak na pozici <code>i</code>. Povolený rozsah je
<code>[0, size()]</code>.</p></li>
<li><p><code>void erase(size_t i)</code>: Smaže znak na pozici
<code>i</code>. Povolený rozsah je <code>[0, size())</code>.</p></li>
<li><p><code>size_t line_start(size_t r) const</code>: Vrátí začátek
<code>r</code>-tého řádku. Znak <code>\n</code> je součástí řádku, který
ukončuje. Povolený rozsah je <code>[0, lines())</code>.</p></li>
<li><p><code>size_t line_length(size_t r) const</code>: Vrátí délku
<code>i</code>-tého řádku včetně případného znaku <code>\n</code> na
konci. Povolený rozsah je <code>[0, lines())</code>.</p></li>
<li><p><code>size_t char_to_line(size_t i) const</code>: Vrátí číslo
řádku, na kterém se nachází <code>i</code>-tý znak. Povolený rozsah je
<code>[0, size())</code>.</p></li>
</ul>
<p>Pokud je metoda volána s argumentem mimo rozsah, musí vyvolat výjimku
<code>std::out_of_range</code>. Metody <code>size</code> a
<code>lines</code> by měly mít konstantní složitost. Ostatní metody by
měly mít logaritmickou složitost. Konstruktor by neměl být pomalejší,
než opakované volání metody <code>insert</code>.</p>
<h2 id="bodové-podmínky">Bodové podmínky</h2>
<ul>
<li>Pro zisk <span class="math inline">1</span> bodu je třeba korektně
implementovat rozhraní, ale na časové složitosti metod (téměř) nezáleží.
(Časový limit je 15 sekund.)</li>
<li>Pro zisk <span class="math inline">5</span> bodů již naivní
implementace nepostačuje, ale operace jsou stále prováděny náhodně. Tedy
testovací prostředí se nesnaží vyvést váš editor z rovnováhy. (Časový
limit je 1 sekunda.)</li>
<li>Pro zisk <span class="math inline">10</span> bodů je potřeba správně
implementovat rozhraní s uvedenými nebo lepšími složitostmi. (Časový
limit je 10 sekund.)</li>
</ul>
</td> 

</tr>
