<td class="header"><b>Příhradová konstrukce</b></td>

<td class="lrtbCell" colspan="3" align="left"><p>Úkolem je realizovat sadu tříd, které budou optimalizovat příhradové konstrukce.</p>

<p>Předpokládáme, že máme zkonstruovat nosník, který bude co nejpevnější a zároveň co nejlevnější.
Nosník bude mít tvar mnohoúhelníku, může být obecně nekonvexní. Takový mnohoúhelník vyztužíme tím, že
přidáme dodatečné výztuhy propojující body mnohoúhelníku. Aby byl nosník co nejpevnější, přidáme
co nejvíce takových dodatečných výztuh, které se nekříží. Výztuhy tak rozdělí
mnohoúhelník na disjunktní trojúhelníky. Úkolem je nalézt umístění výztuh tak, aby se spotřebovalo co
nejméně materiálu, tedy aby součet délek dodaných výztuh byl co nejmenší. Formálně se jedná o problém
minimální triangulace <tt>nekonvexního</tt> mnohoúhelníku.</p>

<p>Druhým úkolem je určit počet různých možností, kterými lze výztuhy umístit. Například pro obdélník
jsou možnosti 2 - můžeme si vybrat jednu z úhlopříček. Pro větší počet stran mnohoúhelníku a složitější
tvary je pak výpočet náročnější. Počet různých triangulací navíc poměrně rychle roste, proto je pro
reprezentaci použit vlastní celočíselný datový typ o velikosti 1024 bitů.</p>

<p>Oba problémy lze řešit v polynomiálním čase se složitostí <tt>O(n<sup>3</sup>)</tt>, proto bude
pro zrychlení výpočtu vhodné zapojit více vláken. Očekávané řešení se musí správně zapojit do níže
popsané infrastruktury a musí správně vytvářet, plánovat, synchronizovat a ukončovat vlákna. Vlastní
algoritmické řešení problému není úplně nutné, testovací prostředí nabízí rozhraní, které dokáže
zadaný problém sekvenčně vyřešit.</p>

<hr />

<p>Problém k vyřešení je reprezentován instancí <tt>CPolygon</tt>. Třída obsahuje členské
proměnné s umístěním jednotlivých bodů mnohoúhelníku a členské proměnné pro vypočtenou minimální
triangulaci a počet triangulací.</p>

<p>Problémy jsou zabalené do skupin (balíků), takovou skupinu reprezentuje třída <tt>CProblemPack</tt>.
V balíku jsou dva oddělené seznamy: v jednom seznamu jsou mnohoúhelníky, kde chceme spočítat minimální
triangulaci, ve druhém pak mnohoúhelníky, kde máme spočítat počet triangulací.</p>

<p>Problém triangulace je zajímavý pro více firem, které se zabývají konstrukcemi. Firmy budou průběžně dodávat
balíky problémů k vyřešení. Zadavatel je realizován třídou <tt>CCompany</tt>. Tato třída obsahuje rozhraní,
které umožní načítání dalších balíků problémů k vyřešení (metoda <tt>waitForPack</tt>) a rozhraní, kterým se
vrací vyřešené balíky problémů zpět (metoda <tt>solvedPack</tt>). Vaše implementace vytvoří 2 pomocná vlákna pro
<b>každou</b> instanci <tt>CCompany</tt>. Jedno vlákno bude v cyklu načítat nové balíky problémů k vyřešení
a předávat je dále ke zpracování. Druhé vlákno bude vyřešené balíky problémů vracet (bude v cyklu volat
<tt>solvedPack</tt>). Tato pomocná vlákna zajišťují komunikaci s řešičem. Nejsou ale určena pro provádění
vlastních výpočtů (řešené problémy jsou výpočetně náročné, komunikační vlákna by nemusela včas předat data).
Úkolem komunikačních vláken je ale zjistit správné pořadí odevzdávání vyřešených balíků problémů, odevzdávat
je potřeba ve stejném pořadí, ve kterém byly problémy načteny. V jednom okamžiku lze načíst více instancí
balíků problémů a mít je rozpracované (je to dokonce žádoucí a nutné). Důležité je ale dodržet pořadí při
jejich odevzdání.</p>

<p>Celý výpočet zapouzdřuje instance <tt>COptimizer</tt>. Tato třída obsahuje odkazy na jednotlivé firmy,
řídí spouštění a pozastavení výpočtu a řídí činnost výpočetních vláken. Výpočetní vlákna jsou použita pro
řešení zadávaných problémů a jsou použita pro řešení problémů ze všech obsluhovaných firem. Výpočetní
vlákna převezmou problém od komunikačního vlákna, provedou vlastní výpočty a vyřešený problém předají
zpět komunikačnímu vláknu (té správné firmy), aby jej toto ve vhodný okamžik předalo zpět (je potřeba
dodržet pořadí). Výpočetních vláken bude existovat právě a pouze zadaný počet, to umožní vhodně
využít hardwarové vybavení počítače (počet CPU).</p>

<p>Třída <tt>COptimizer</tt> bude použita podle následujícího scénáře:</p>
<ul>
 <li>vytvoří se instance <tt>COptimizer</tt>,</li>
 <li>voláním metody <tt>addCompany</tt> se zaregistrují jednotlivé firmy,</li>
 <li>spustí se vlastní výpočet (voláním metody <tt>start</tt>). Metoda <tt>start</tt> dostane v parametru
   počet výpočetních vláken (<tt>workThreads</tt>). Tato vlákna vytvoří a nechá je čekat na příchozí požadavky.
   Zároveň pro každou zaregistrovanou firmu vytvoří dvě komunikační vlákna, jedno pro příjem požadavků a druhé pro
   odevzdávání výsledků. Po spuštění vláken se metoda <tt>start</tt> vrátí zpět do volajícího,</li>
 <li>komunikační vlákna průběžně přebírají požadavky (v cyklu volají odpovídající metody
     <tt>waitForPack</tt>). Vlákno přebírající požadavky se ukončí v okamžiku, kdy načtete prázdný požadavek (smart
     pointer obsahuje <tt>nullptr</tt>),</li>
 <li>výpočetní vlákna přebírají problémy od komunikačních vláken a řeší je. Po vyřešení problém předají
     odevzdávacímu vláknu odpovídající firmy,</li>
 <li>odevzdávací vlákna čekají na vyřešené problémy a vyhodnocují, které balíky problémů jsou již zcela vyřešené.
    Po vyřešení celého balíku problémů bude tento balík vrácen zadávající firmě (metoda <tt>solvedPack</tt>).
    Vyřešené balíky problémů musíte odevzdat okamžitě, jak to je (vzhledem k pořadí) možné (vyřešené balíky problémů
    nelze ukládat a odevzdat až na konci výpočtu). Odevzdávací vlákno skončí, pokud již žádné další problémy z dané
    firmy nepřijdou (<tt>waitForPack</tt> dříve vrátil <tt>nullptr</tt>) a všechny balíky problémů této firmy byly
    vyřešené a odevzdané,</li>
 <li>testovací prostředí v nějakém okamžiku zavolá metodu <tt>stop</tt>. Volání počká na dokončení obsluhy všech
     firem, ukončí pracovní vlákna a vrátí se do volajícího,</li>
 <li>je uvolněna instance <tt>COptimizer</tt>.</li>
</ul>

Použité třídy a jejich rozhraní:
<ul>
  <li><tt>CPoint</tt> je třída reprezentující jeden bod mnohoúhelníku. Jedná se o velmi jednoduchou
    třídu, která zapouzdřuje dvojici celých čísel - souřadnice. Třída je implementovaná
    v testovacím prostředí, její rozhraní nesmíte nijak měnit. Rozhraní obsahuje:
    <ul>
      <li><tt>m_X</tt> souřadnice x,</li>
      <li><tt>m_Y</tt> souřadnice y.</li>
    </ul>
  </li>

  <li><tt>CPolygon</tt> je třída reprezentující jeden mnohoúhelník. Jedná se o abstraktní třídu, její implementace
    (přesněji, implementace potomka) je hotová v testovacím prostředí. Rozhraní nesmíte nijak měnit. Rozhraní obsahuje:
    <ul>
      <li><tt>m_Points</tt> vektor souřadnic s vrcholy mnohoúhelníku,</li>
      <li><tt>m_TriangMin</tt> členská proměnná, kam bude uložena vypočtená délka minimální triangulace. Uložena hodnota
        bude zahrnovat součet délek stran mnohoúhelníku plus součet délek dodaných uhlopříček.</li>
      <li><tt>m_TriangCnt</tt> členská proměnná, kam bude uložen vypočtený počet různých triangulací daného
        mnohoúhelníku.</li>
      <li>třída dále obsahuje konstruktor a metodu <tt>add</tt> pro zjednodušení práce (viz přiložená implementace).</li>
    </ul>
  </li>

  <li><tt>CProblemPack</tt> je třída reprezentující balík problémů k vyřešení. Jedná se o abstraktní třídu, její implementace
    (přesněji, implementace potomka) je hotová v testovacím prostředí. Rozhraní nesmíte nijak měnit. Rozhraní obsahuje:
    <ul>
      <li><tt>m_ProblemsMin</tt> pole instancí problémů k vyřešení, požaduje se výpočet minimální triangulace,</li>
      <li><tt>m_ProblemsCnt</tt> pole instancí problémů k vyřešení, požaduje se výpočet počtu triangulací,</li>
      <li>třída dále obsahuje metodu <tt>addMin</tt> a <tt>addCnt</tt> pro zjednodušení práce (viz přiložená implementace).</li>
    </ul>
  </li>

  <li><tt>CCompany</tt> je třída reprezentující jednu firmu. Třída pouze definuje rozhraní,
    faktická implementace v testovacím prostředí je potomkem <tt>CCompany</tt>. Rozhraní třídy
    tedy nemůžete měnit. K dispozici jsou metody:
    <ul>
      <li><tt>waitForPack</tt> pro načtení dalšího balíku problémů z firmy. Metoda vrátí instanci ke zpracování
        nebo neplatný ukazatel (smart pointer obsahuje <tt>nullptr</tt>), pokud již nejsou pro tuto firmu
        další instance balíků problémů ke zpracování. Volání metody může trvat dlouho, proto pro obsluhu musíte vyčlenit
        oddělené komunikační vlákno, které bude metodu v cyklu volat. Vlákno nesmí provádět žádnou výpočetně náročnou
        činnost, musí získanou instanci <tt>CProblemPack</tt> předat ke zpracování pracovním vláknům. Kontroluje se, že
        v jedné instanci firmy volá tuto metodu vždy jedno (stejné) vlákno,</li>

      <li><tt>solvedPack</tt> pro předání vyřešené instance <tt>CProblemPack</tt>. Parametrem je vyřešená instance
        balíku problému dříve získaná z volání <tt>waitForPack</tt>. Protože odevzdání může trvat dlouho, musíte pro
        odevzdávání vytvořit vyhrazené komunikační vlákno. Vlákno bude přebírat od pracovních vláken vyřešené instance
        problémů, rozhodne, které balíky problémů jsou zcela vyřešené a zavolá na ně metodu <tt>solvedPack</tt>. Vyřešené
        instance balíků problémů musí být vracené ve stejném pořadí, ve kterém byly z <tt>waitForPack</tt> převzaté. Předávací
        vlákno nesmí provádět žádnou výpočetně náročnou činnost. Kontroluje se, že v jedné instanci firmy volá tuto metodu vždy
        jedno (stejné) vlákno.</li>
    </ul>
  </li>

  <li><tt>CBigInt</tt> je třída implementující velká celá kladná čísla. Čísla jsou reprezentovaná binárně pomocí
    1024 bitů. Třída je implementovaná jednak v testovacím prostředí a dále je k dispozici i v dodané knihovně. Implementace
    je omezena pouze na základní operace: nastavení hodnoty (z <tt>uint64_t</tt> a z desítkového zápisu v řetězci), převod
    hodnoty na řetězec v desítkovém zápisu, sčítání, násobení a porovnání. Ostatní operace nejsou k dispozici a nejsou
    pro implementaci potřeba.</li>

  <li><tt>COptimizer</tt> je třída zapouzdřující celý výpočet. Třídu budete vytvářet vy, musíte ale dodržet
    následující veřejné rozhraní:
    <ul>
     <li>konstruktor bez parametrů inicializuje novou instanci třídy. Zatím nevytváří žádná vlákna,</li>

     <li>metodu <tt>addCompany (x)</tt>, tato metoda zaregistruje firmu <tt>x</tt>,</li>

     <li>metodu <tt>start ( workThr )</tt>, tato metoda vytvoří komunikační vlákna pro všechny zaregistrované
       firmy a spustí <tt>workThr</tt> pracovních vláken. Po spuštění vláken se metoda <tt>start</tt>
       vrátí zpět do volajícího,</li>

     <li>metodu <tt>stop</tt>, která počká na dokončení obsluhy firem a ukončení vytvořených
       vláken. Po tomto se volání <tt>stop</tt> vrátí zpět do volajícího,</li>

     <li>metoda <tt>usingProgtestSolver()</tt> vrátí hodnotu <tt>true</tt>, pokud pro vlastní řešení
       problémů používáte dodaný řešič <tt>CProgtestSolver</tt> nebo hodnotu <tt>false</tt> pokud
       celý výpočet implementujete vlastním kódem. Pokud tato metoda vrací <tt>true</tt>, testovací prostředí
       nepoužívá metody <tt>COptimizer::checkAlgorithmMin()</tt> a <tt>COptimizer::checkAlgorithmCnt()</tt>
       níže (můžete je ponechat prázdné). Pokud metoda vrací <tt>false</tt>, testovací prostředí upraví chování
       poskytovaného řešiče <tt>CProgtestSolver</tt> tak, že úmyslně vyplňuje nesprávné výsledky.</li>

     <li>třídní metodu <tt>checkAlgorithmMin(polygon)</tt>. Metoda slouží k otestování správnosti vlastního algoritmu
       výpočtu. Parametrem volání je jedna instance <tt>CPolygon</tt>. Kód metody zajistí potřebné výpočty a vyplní
       složku <tt>m_TriangMin</tt> v instanci <tt>polygon</tt>. Kromě kontroly správnosti implementovaných algoritmů
       se metoda používá ke kalibraci rychlosti vašeho řešení. Rychlosti se přizpůsobí velikost zadávaných problémů,
       aby testování trvalo rozumně dlouhou dobu. Metodu implementujte pouze pokud nepoužíváte dodaný řešič problémů
       <tt>CProgtestSolver</tt> (tedy pokud Vaše metoda <tt>COptimizer::usingProgtestSolver()</tt> vrací <tt>false</tt>),</li>

     <li>třídní metodu <tt>checkAlgorithmCnt(polygon)</tt>. Metoda slouží k otestování správnosti vlastního algoritmu
       výpočtu. Parametrem volání je jedna instance <tt>CPolygon</tt>. Kód metody zajistí potřebné výpočty a vyplní
       složku <tt>m_TriangCnt</tt> v instanci <tt>polygon</tt>. Kromě kontroly správnosti implementovaných algoritmů
       se metoda používá ke kalibraci rychlosti vašeho řešení. Rychlosti se přizpůsobí velikost zadávaných problémů,
       aby testování trvalo rozumně dlouhou dobu. Metodu implementujte pouze pokud nepoužíváte dodaný řešič problémů
       <tt>CProgtestSolver</tt> (tedy pokud Vaše metoda <tt>COptimizer::usingProgtestSolver()</tt> vrací <tt>false</tt>),</li>
    </ul>
  </li>

  <li><tt>CProgtestSolver</tt> je třída poskytující rozhraní pro sekvenční řešení zadávaných problémů. Její autor
    se rozhodl trochu zpestřit její používání, proto je chování této třídy poněkud rozverné. Třída <tt>CProgtestSolver</tt>
    je abstraktní, vlastní implementace je realizovaná podtřídami. Instance potomků <tt>CProgtestSolver</tt> se vytvářejí
    pomocí factory funkcí <tt>createProgtestMinSolver()</tt> (umí řešit problémy minimální triangulace) a
    <tt>createProgtestCntSolver()</tt> (umí řešit problémy nalezení počtu triangulací). Instance <tt>CProgtestSolver</tt>
    navíc řeší zadávané problémy dávkově. Každá instance <tt>CProgtestSolver</tt> má určenou kapacitu, kolik instancí
    problému do ní lze nejvýše umístit. Instance <tt>CProgtestSolver</tt> se používá pouze jednorázově. Pokud je potřeba
    vyřešit další instance problémů, je potřeba vyrobit další instanci <tt>CProgtestSolver</tt>. Třída má následující rozhraní:
    <ul>
     <li><tt>hasFreeCapacity()</tt> metoda vrátí <tt>true</tt>, pokud lze do instance umístit další instanci problému
       k vyřešení, <tt>false</tt>, pokud je instance zcela zaplněná,</li>
     <li><tt>addPolygon(x)</tt> metoda přidá instanci problému <tt>x</tt> k vyřešení. Návratovou hodnotou je <tt>true</tt>
       pokud byl problém přidán, <tt>false</tt> pokud ne (protože byla dosažena kapacita řešiče). Po vložení problému
       je rozumné otestovat, zda je kapacita řešiče zaplněná (<tt>hasFreeCapacity</tt>). Pokud je kapacita využitá,
       spusťte výpočet (<tt>solve</tt>).</li>
     <li><tt>solve()</tt> metoda spustí vlastní výpočet. Pro vložené instance se určí výsledek a umístí se do
       odpovídající složky <tt>m_TriangMin</tt> / <tt>m_TriangCnt</tt>. Metoda nedělá nic dalšího, zejména se nepokouší
       informovat o vyřešení zadaných problémů (nevolá <tt>CCompany::solvedPack</tt>). Další zpracování vyřešených
       problémů je čistě Vaše zodpovědnost. Metodu <tt>solve</tt> lze zavolat pro danou instanci <tt>CProgtestSolver</tt>
       pouze jednou, další pokusy skončí chybou. Metoda vrací počet vyřešených instancí problémů, návratová hodnota
       0 typicky znamená chybu (opakovaný pokus o volání metody).</li>
    </ul>
    <p>Instance <tt>CProgtestSolver</tt> nedovolí vložit více problémů než je její kapacita. Na druhou stranu, metodu
      <tt>solve</tt> lze zavolat kdykoliv (ale jen jednou pro danou instanci). Nepokoušejte se ale řešič zneužívat
      a řešit problémy pouze po jednom:</p>
    <ul>
     <li>testovací prostředí vytváří instance <tt>CProgtestSolver</tt> tak, že součet jejich kapacit <tt>M</tt> pokrývá celkový
       počet zadávaných problémů <tt>N</tt> v testu (typicky <tt>M</tt> je o něco málo větší než <tt>N</tt>),</li>
     <li>pokud byste každou instanci <tt>CProgtestSolver</tt> využili pouze k vyřešení jedné instance problému, brzy vyčerpáte
       kapacitu <tt>M</tt> a další zadávané problémy nebudete mít jak řešit,</li>
     <li>pokud překročíte kapacitu <tt>M</tt>, budou volání <tt>createProgtestMinSolver()</tt> / <tt>createProgtestCntSolver()</tt>
       vracet neužitečné instance řešičů (podle nálady bude vrácen prázdný smart pointer, řešič bude mít kapacitu 0 nebo bude úmyslně
       vyplňovat nesprávné výsledky),</li>
     <li>proto je důležité kapacitu řešičů využívat naplno,</li>
     <li>kapacity jednotlivých instancí řešičů jsou volené náhodně. Jak již bylo řečeno, tato třída se snaží
       zpestřit programátorům nudnou práci.</li>
    </ul>
    <p>Dále, testovacím prostředím poskytovaný řešič je k dispozici pouze v povinných a nepovinných testech (není k dispozici
      v bonusových testech). Pokud se jej v bonusovém testu pokusíte použít, bude factory funkce <tt>createProgtestMinSolver()</tt> /
      <tt>createProgtestCntSolver()</tt> vracet prázdné instance, případně instance s nulovou kapacitou či počítající nesprávné výsledky.</p>
  </li>

  <li><tt>createProgtestMinSolver</tt> - funkce vytvoří instanci <tt>CProgtestSolver</tt>, která bude řešit problémy minimální triangulace.</li>

  <li><tt>createProgtestCntSolver</tt> - funkce vytvoří instanci <tt>CProgtestSolver</tt>, která bude řešit problémy nalezení počtu triangulací.</li>
</ul>

<hr />

<p>Odevzdávejte zdrojový kód s implementací požadované třídy
<tt>COptimizer</tt> s požadovanými metodami. Můžete samozřejmě přidat
i další podpůrné třídy a funkce. Do Vaší implementace nevkládejte funkci
<tt>main</tt> ani direktivy pro vkládání hlavičkových souborů. Funkci
<tt>main</tt> a hlavičkové soubory lze ponechat pouze v případě, že jsou
zabalené v bloku podmíněného překladu.</p>

<p>Využijte přiložený ukázkový soubor. Celá implementace patří do souboru
<tt>solution.cpp</tt>. Pokud zachováte bloky podmíněného překladu, můžete
soubor <tt>solution.cpp</tt> odevzdávat jako řešení úlohy.</p>

<p>Při řešení lze využít pthread nebo C++11 API pro práci s vlákny (viz
vložené hlavičkové soubory). Dostupný je kompilátor g++ verze 12.2, tato verze
kompilátoru zvládá většinu C++11, C++14, C++17 a C++20 konstrukcí (některé
okrajové vlastnosti C++20 nejsou podporované plně).</p>

<hr />

<b>Doporučení:</b><br />

<ul>
 <li>Začněte se rovnou zabývat vlákny a synchronizací, nemusíte se zabývat
   vlastními algoritmy řešení zadaných problémů. Využijte dodané řešení -
   třídu <tt>CProgtestSolver</tt>. Až budete mít hotovou synchronizaci,
   můžete doplnit i vlastní algoritmické řešení.</li>

 <li>Abyste zapojili co nejvíce jader, obsluhujte co nejvíce instancí <tt>CPolygon</tt> najednou.
   Je potřeba zároveň přebírat problémy, řešit je a odevzdávat je. Nepokoušejte se
   tyto činnosti nafázovat (například nejdříve pouze počkat na všechny <tt>CProblemPack</tt>,
   pak začít řešit akumulované problémy, ...), takový postup nebude fungovat.
   Testovací prostředí je nastaveno tak, aby takové "serializované" řešení vedlo
   k uváznutí (deadlock).</li>

 <li>Instance <tt>COptimizer</tt> je vytvářená opakovaně, pro různé vstupy.
   Nespoléhejte se na inicializaci globálních proměnných - při druhém a dalším
   zavolání budou mít globální proměnné hodnotu jinou. Je rozumné případné globální
   proměnné vždy inicializovat v konstruktoru nebo na začátku metody <tt>start</tt>.
   Ještě lepší je nepoužívat globální proměnné vůbec.</li>

 <li>Nepoužívejte mutexy a podmíněné proměnné inicializované pomocí
   <tt>PTHREAD_MUTEX_INITIALIZER</tt>, důvod je stejný jako v minulém odstavci.
   Použijte raději <tt>pthread_mutex_init()</tt> nebo C++11 API.</li>

 <li>Instance problémů (<tt>CPolygon</tt>), balíků problémů (<tt>CProblemPack</tt>),
   firem (<tt>CCompany</tt>) a řešičů (<tt>CProgtestSolver</tt>) alokovalo testovací
   prostředí při vytváření příslušných smart pointerů. K uvolnění dojde automaticky po
   zrušení všech odkazů. Uvolnění těchto instancí tedy není Vaší starostí, stačí
   zapomenout všechny takto předané smart pointery. Váš program je ale
   zodpovědný za uvolnění všech ostatních prostředků, které si sám alokoval.</li>

 <li>Neukončujte metodu <tt>stop</tt> pomocí <tt>exit</tt>,
   <tt>pthread_exit</tt> a podobných funkcí. Pokud se funkce <tt>stop</tt>
   nevrátí do volajícího, bude Vaše implementace vyhodnocena jako nesprávná.</li>

 <li>Využijte přiložená vzorová data. V archivu jednak naleznete ukázku
   volání rozhraní a dále několik testovacích vstupů a odpovídajících výsledků.</li>

 <li>V testovacím prostředí je k dispozici STL. Myslete ale na to, že ten samý STL
   kontejner nelze najednou zpřístupnit z více vláken. Více si o omezeních přečtěte např.
   na <a href="http://en.cppreference.com/w/cpp/container">C++ reference - thread safety.</a></li>

 <li>Testovací prostředí je omezené velikostí paměti. Není uplatňován žádný explicitní limit, ale VM,
   ve které testy běží, je omezena 4 GiB celkové dostupné RAM. Úloha může být dost paměťově náročná,
   zejména pokud se rozhodnete pro jemné členění úlohy na jednotlivá vlákna. Pokud se rozhodnete pro
   takové jemné rozčlenění úlohy, možná budete muset přidat synchronizaci běhu vláken tak, aby celková
   potřebná paměť v žádný okamžik nepřesáhla rozumný limit. Pro běh máte garantováno, že Váš program
   má k dispozici nejméně 1 GiB pro Vaše data (data segment + stack + heap). Pro zvídavé - zbytek do
   4GiB je zabraný běžícím OS, dalšími procesy, zásobníky Vašich vláken a nějakou rezervou.</li>

 <li>Výpočetně náročné operace musí provádět pracovní vlákna. Počet
   pracovních vláken je určen parametrem metody <tt>COptimizer::start</tt>. Testovací
   prostředí kontroluje, zda Vaše implementace neprovádí výpočetně náročné
   operace v ostatních vláknech. Pokud to zjistí, Vaše řešení bude
   odmítnuto.</li>

 <li>Explicitní nastavení počtu pracovních vláken má dobré praktické důvody.
   Volbou rozumného počtu pracovních vláken můžeme systém zatížit dle naší
   volby (tedy například podle počtu jader, která můžeme úloze přidělit).
   Pokud by časově náročné výpočty probíhaly i v jiných vláknech (komunikační
   vlákna), pak by bylo možné systém snadno zahltit například při velkém množství
   registrovaných firem.</li>
</ul>

<b>Doporučení pro implementaci vlastního algoritmického řešení:</b><br />

<ul>
 <li>Vlastní algoritmické řešení není nutné, je k dispozici dodaný <tt>CProgtestSolver</tt>.
   Použité algoritmy nejsou obtížné, ale můžete narazit na nepříjemné problémy z analytické
   geometrie (průsečíky úseček, zaokrouhlovací chyby, neceločíselná aritmetika).</li>

 <li><tt>CProgtestSolver</tt> se snaží vyhnout výpočtům v plovoucí desetinné čárce,
   zejména při výpočtu průsečíků úseček. To se daří díky tomu, že zadané souřadnice jsou celá
   čísla typu <tt>int</tt> a při výpočtu stačí pracovat se zlomky, kde čitatel i jmenovatel má
   typ <tt>int</tt> (rovnice lze následně přenásobit jmenovatelem a pracovat v typu
   <tt>long int</tt>). Desetinná čísla jsou použitá pouze pro finální výpočet délky triangulace.</li>

 <li>Zadávané mnohoúhelníky mohou být konvexní i nekonvexní. Pro nekonvexní mnohoúhelníky jsou
   algoritmy často komplikovanější a časově náročnější. Testovací prostředí zadává pouze "hezké"
   nekonvexní mnohoúhelníky: zadávané mnohoúhelníky neobsahují "díry" a strany zadávaných mnohoúhelníků
   se neprotínají (simple polygon). Díky tomuto omezení vychází algoritmy ještě zvládnutelně.</li>

 <li>Algoritmus minimální triangulace konvexních polygonů je oblíbený problém pro aplikaci
   dynamického programování. Rozšíření pro nekonvexní polygony je přímočaré, jen je potřeba
   kontrolovat možnost dělení polygonů v daném místě.</li>

 <li>Výpočet celkového počtu triangulací je opět aplikací dynamického programování. Pro konvexní
   polygony je pro výpočet k dispozici explicitní vzorec - počet triangulací je Catalaniho číslo.
   Výpočet pro nekonvexní polygon vychází z myšlenky odvození vzorce pro konvexní polygony, jen
   je potřeba eliminovat některá dělení, která v nekonvexním polygonu nejsou přípustná.</li>

 <li>Vaše implementace řešiče musí mít rozumnou složitost. Implementované řešení má časovou složitost
   <tt>O(n<sup>3</sup>)</tt> a paměťovou složitost <tt>O(n<sup>2</sup>)</tt>, tyto složitosti platí
   pro oba řešené problémy. Pro výpočet počtu triangulací se ale dá očekávat výrazně vyšší
   multiplikativní konstanta (práce s velkými čísly).</li>

 <li>Pokud správně implementujete vlastní řešení se stejnými složitostmi, vyhoví pro kompletní vyřešení
   této úlohy. Jak již bylo uvedeno výše, testovací prostředí kalibruje rychlost použitého algoritmu a
   naměřenou rychlost používá pro nastavení velikosti řešených problémů. Díky tomu si v určitých mezích
   dokáže poradit s různě efektivními implementacemi.</li>

 <li>Pro úspěšné zvládnutí bonusu #2 a #3 je potřeba zapojit více vláken i do výpočtu triangulace
   jednotlivých polygonů. Polygony zadávané v těchto testech mají typicky několik stovek vrcholů.</li>
</ul>

<hr />

<b>Co znamenají jednotlivé testy:</b><br />
<dl>
 <dt><b>Test algoritmu (sekvencni)</b></dt><dd>Testovací prostředí opakovaně
   volá metody <tt>checkAlgorithmMin()</tt> / <tt>checkAlgorithmCnt()</tt> pro různé
   vstupy a kontroluje vypočtené výsledky. Slouží pro otestování implementace Vašeho algoritmu.
   Není vytvářena instance <tt>COptimizer</tt> a není volaná metoda <tt>start</tt>.
   Na tomto testu můžete ověřit, zda Vaše implementace algoritmu je dostatečně rychlá.
   Testují se náhodně generované problémy, nejedná se o data z dodané ukázky.
   Pokud <tt>COptimizer::usingProgtestSolver</tt> vrací <tt>true</tt>, tento test
   se efektivně přeskočí.</dd>

 <dt><b>Základní test</b></dt><dd>Testovací prostředí vytváří instanci
   <tt>COptimizer</tt> pro různý počet firem a pracovních vláken.
   Ve jménu testu je pak uvedeno, kolik je firem (C=xxx) a pracovních
   vláken (W=xxx). </dt>

 <dt><b>Základní test (W=n, C=m)</b></dt><dd><p>V tomto testu se navíc kontroluje,
   zda průběžně odevzdáváte již vyřešené instance balíků problémů. Testovací prostředí
   v jednom okamžiku přestane dodávat nové balíky problémy, dokud nejsou všechny dosud
   zadané balíky problémů vyřešené a vrácené. Pokud nepřebíráte/neřešíte/neodevzdáváte
   balíky problémů průběžně, skončíte v tomto testu deadlockem.</p>

   <p>Pokud používáte <tt>CProgtestSolver</tt>, vždy využívejte plně jeho kapacitu.
   V tomto testu jde požadavek na kompletní využití kapacity instance
   <tt>CProgtestSolver</tt> proti požadavku na průběžné řešení a odevzdávání
   vyřešených balíků problémů. Testovací prostředí v tomto testu dodává instance
   <tt>CProgtestSolver</tt> vždy s kapacitou 1, tedy <b>nemůže</b> nastat situace,
   kdy čekáte na další balík problémů (aby se využila kapacita řešiče) a zároveň testovací
   prostředí čeká na odevzdání zadaných balíků problémů (aby pokračovalo v zadávání).</p></dt>

 <dt><b>Test zrychleni vypoctu</b></dt><dd>Testovací prostředí spouští Vaši
   implementaci pro ta samá vstupní data s různým počtem pracovních vláken. Měří
   se čas běhu (real i CPU). S rostoucím počtem vláken by měl real time klesat, CPU time
   mírně růst (vlákna mají možnost běžet na dalších CPU). Pokud real time
   neklesne, nebo klesne málo (např. pro 2 vlákna by měl ideálně klesnout na
   0.5, je ponechaná určitá rezerva), test není splněn.</dd>

 <dt><b>Busy waiting (pomale waitForPack)</b></dt><dd>Nové balíky problémů jsou předávané pomalu.
   Výpočetní vlákna tím nemají práci. Pokud tato vlákna
   nejsou synchronizovaná blokujícím způsobem, výrazně vzroste CPU time a test
   selže.</dd>

 <dt><b>Busy waiting (pomale solvedPack)</b></dt><dd>Odevzdávání vyřešených balíků problémů
   je pomalé. Vyřešené problémy nemá od výpočetních vláken kdo přebírat. Pokud tato
   vlákna nejsou synchronizovaná blokujícím způsobem, výrazně vzroste CPU time
   a test selže.</dd>

 <dt><b>Rozlozeni zateze #1</b></dt><dd>Testovací prostředí zkouší, zda
   se do řešení jedné instance <tt>CProblemPack</tt> dokáže zapojit více pracovních
   vláken. V instanci je více zadání problémů, tato zadání
   mohou být řešena nezávisle více pracovními vlákny. V testu není k dispozici
   <tt>CProgtestSolver</tt>.</dd>

 <dt><b>Rozlozeni zateze #2</b></dt><dd>Testovací prostředí zkouší, zda
   se do řešení jedné instance problému minimální triangulace dokáže zapojit více pracovních
   vláken. V instanci <tt>CProblemPack</tt> je zadán pouze jeden polygon s velkým počtem vrcholů,
   do jeho řešení je potřeba zapojit více (všechna) pracovní vlákna. V testu není
   k dispozici <tt>CProgtestSolver</tt>.</dd>

 <dt><b>Rozlozeni zateze #3</b></dt><dd>Testovací prostředí zkouší, zda
   se do řešení jedné instance problému zjištění počtu triangulací dokáže zapojit
   více pracovních vláken. V instanci <tt>CProblemPack</tt> je zadán pouze jeden problém
   s velkým počtem vrcholů, do jeho řešení je potřeba zapojit více (všechna) pracovní vlákna.
   V testu není k dispozici <tt>CProgtestSolver</tt>.</dd>
</dl>





</td> 

</tr>
