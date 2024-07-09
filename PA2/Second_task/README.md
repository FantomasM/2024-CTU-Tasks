<td class="header"><b>Evidence zaměstnanců</b></td>

<td class="lrtbCell" colspan="3" align="left"><p>Úkolem je realizovat třídu <tt>CPersonalAgenda</tt>, která bude implementovat
databázi zaměstnanců.</p>

<p>Pro usnadnění práce HR oddělení máme realizovanou databázi zaměstnanců. Pro sledované 
zaměstnance si pamatujeme jméno, příjmení, email a plat. V průběhu evidence zaměstnance se 
tyto údaje mohou měnit, údaje chceme vyhledávat a chceme mít přehled o platech.</p>

<p>Zaměstnanec je identifikován svým jménem a příjmením nebo svým e-mailem. Firemní postupy 
zajišťují, že e-mail je unikátní přes celou databázi. Dále, jména a příjmení se mohou 
opakovat, ale dvojice (jméno, příjmení) je opět v databázi unikátní. Tedy v databázi 
může být mnoho lidí s příjmením <tt>Svoboda</tt>, mnoho lidí může mít jméno <tt>Petr</tt>,
ale zaměstnanec <tt>Svoboda Petr</tt> může být v databázi v daném okamžiku pouze jeden. 
Při porovnávání jmen, příjmení i e-mailů rozlišujeme malá a velká písmena (case sensitive).</p>  


<p>Veřejné rozhraní je uvedeno níže. Obsahuje následující:</p>
<ul>
 <li>Konstruktor bez parametrů. Tento konstruktor inicializuje instanci třídy 
  tak, že vzniklá instance je zatím prázdná (neobsahuje žádné záznamy).</li>
  
 <li>Destruktor. Uvolňuje prostředky, které instance alokovala.</li>
 
 <li>Metoda <tt>add(name, surname, email, salary)</tt> přidá do existující
  databáze další záznam. Parametry <tt>name</tt> a <tt>surname</tt> reprezentují 
  jméno a příjmení, parametr <tt>email</tt> udává mailovou adresu a <tt>salary</tt> plat.  
  Metoda vrací hodnotu <tt>true</tt>, pokud byl záznam přidán, nebo hodnotu <tt>false</tt>, 
  pokud přidán nebyl (protože již  v databázi existoval záznam se stejným 
  jménem a příjmením,  nebo záznam se stejným e-mailem).</li>
  
 <li>Metody <tt>del (name, surname) / del (email)</tt> odstraní záznam 
  z databáze. Parametrem je jednoznačná identifikace pomocí jména a příjmení (první varianta) 
  nebo pomocí emailu (druhá varianta). Pokud byl záznam skutečně odstraněn, 
  vrátí metoda hodnotu <tt>true</tt>. Pokud záznam odstraněn nebyl (protože neexistoval zaměstnanec 
  s touto identifikací), vrátí metoda hodnotu <tt>false</tt>.</li>
  
 <li>Metoda <tt>changeName(email, newName, newSurname)</tt> změní zaměstnanci jeho jméno a příjmení. 
  Zaměstnanec je identifikován pomocí e-mailu <tt>email</tt>, jméno zaměstnance je změněno na 
  <tt>newName/newSurname</tt>. Metoda vrátí <tt>true</tt> pro úspěch, <tt>false</tt> pro chybu 
  (neexistuje zaměstnanec s takovým e-mailem, nově přidělené jméno/příjmení není unikátní).</li>
   
 <li>Metoda <tt>changeEmail(name, surname, newEmail)</tt> změní zaměstnanci jeho email. 
  Zaměstnanec je identifikován pomocí jména a příjmení <tt>name/surname</tt>, e-mail zaměstnance 
  je změněn na <tt>newEmail</tt>. Metoda vrátí <tt>true</tt> pro úspěch, <tt>false</tt> pro chybu 
  (neexistuje zaměstnanec s takovým jménem a příjmením, nově přidělený e-mail není unikátní).</li>
  
 <li>Metody <tt>setSalary (name, surname, salary) / setSalary (email, salary)</tt> změní 
  výši výplaty zadanému zaměstnanci. Varianty jsou dvě - zaměstnanec je identifikován buď svým 
  jménem a příjmením, nebo svojí e-mailovou adresou. Pokud metoda uspěje, vrací <tt>true</tt>, 
  pro neúspěch vrací <tt>false</tt> (neexistující zaměstnanec).</li>

 <li>Metody <tt>getSalary (name, surname) / getSalary (email)</tt> zjistí
  výši výplaty zadaného zaměstnance. Varianty jsou dvě - zaměstnanec je identifikován buď svým 
  jménem a příjmením, nebo svojí e-mailovou adresou. Pokud metoda uspěje, vrací výši výplaty 
  zaměstnance, pro neúspěch (neexistující zaměstnanec) vrací hodnotu 0.</li>

 <li>Metody <tt>getRank (name, surname, rankMin, rankMax) / getRank (email, rankMin, rankMax)</tt> 
  zjistí jak dobře je zaměstnanec placen ve vztahu k ostatním. Výsledkem je pozice výplaty zadaného 
  zaměstnance na pomyslném žebříčku výplat od nejhorší (nejnižší) k nejlepší (nejvyšší). Parametrem 
  je identifikace zaměstnance (podle varianty buď jménem a příjmením, nebo e-mailovou adresou), parametry 
  <tt>rankMin/rankMax</tt> jsou výstupní, do nich funkce zapíše pozici výplaty hledaného zaměstnance 
  v žebříčku. Protože stejnou výplatu může dostávat více zaměstnanců, je výstupem dvojice hodnot - interval min-max.
  Pokud například hledaný zaměstnanec dostává výplatu 20000, 37 zaměstnanců dostává výplatu nižší a 21
  dalších zaměstnanců dostává výplatu stejnou (tedy plat 20000 dostává celkem 22 zaměstnanců), pak 
  výsledkem je <tt>rankMin=37</tt> a <tt>rankMax=37+22-1=58</tt>. Návratovou hodnotou funkce je <tt>true</tt> 
  pro úspěch (zadaný zaměstnanec nalezen, výstupní parametry vyplněny) nebo <tt>false</tt> (zadaný 
  zaměstnanec nenalezen, výstupní  parametry ponechány beze změn).</li>

 <li>Metoda <tt>getFirst ( outName, outSurname )</tt> slouží pro procházení databází. Zaměstnance chceme 
  procházet podle abecedy (seřazené vzestupně podle příjmení, v případě stejných příjmení podle jména). Metoda 
  vrátí prvního zaměstnance v takto seřazeném seznamu, jeho jméno a příjmení zapíše do zadaných výstupních 
  parametrů <tt>outName/outSurname</tt>. Návratovou hodnotou je <tt>true</tt> pro úspěch (databáze nebyla 
  prázdná) nebo <tt>false</tt> (prázdná databáze, výstupní parametry ponechány beze změn).</li>
  
 <li>Metoda <tt>getNext ( name, surname, outName, outSurname )</tt> slouží k procházení zaměstnanců podobně 
  jako metoda <tt>getFirst</tt>. Tato metoda vrátí dalšího zaměstnance, který v seřazeném seznamu zaměstnanců 
  (viz <tt>getFirst</tt>) následuje po zaměstnanci <tt>name/surname</tt>. Jméno následujícího zaměstnance 
  zapíše do zadaných výstupních parametrů <tt>outName/outSurname</tt>. Návratovou hodnotou je <tt>true</tt> 
  pro úspěch (zaměstnanec <tt>name/surname</tt> nalezen a není poslední v seřazeném seznamu) nebo <tt>false</tt> 
  pro neúspěch (zaměstnanec <tt>name/surname</tt> nenalezen nebo je poslední v seznamu). V případě neúspěchu metoda 
  nebude měnit výstupní parametry <tt>outName/outSurname</tt>.</li>
</ul>

<p>Odevzdávejte soubor, který obsahuje implementovanou třídu
<tt>CPersonalAgenda</tt>. Třída musí splňovat veřejné rozhraní podle ukázky - pokud Vámi 
odevzdané řešení nebude obsahovat popsané rozhraní, dojde k chybě při kompilaci. Do třídy 
si ale můžete doplnit další metody (veřejné nebo i privátní) a členské proměnné. Dále si do 
odevzdávaného souboru můžete doplnit další podpůrné funkce nebo třídy.
Odevzdávaný soubor musí obsahovat jak deklaraci třídy (popis rozhraní), tak i definice 
metod, konstruktoru a destruktoru. Je jedno, zda jsou metody implementované inline 
nebo odděleně. Odevzdávaný soubor nesmí obsahovat vkládání hlavičkových souborů a 
funkci <tt>main</tt> (funkce <tt>main</tt> a vkládání hlavičkových souborů může zůstat, 
ale pouze obalené direktivami podmíněného překladu). Za základ implementace použijte 
přiložený zdrojový soubor.</p>

<p>Rozhraní třídy obsahuje řadu metod ve dvou variantách, které se liší pouze způsobem 
identifikace zaměstnance. Je vhodné věnovat nenulový čas návrhu třídy tak, abyste všechen 
výkonný kód nekopírovali 2x (např. realizujte privátní metody, které budete volat z více 
veřejných metod).</p>

<p>Třída je testovaná v omezeném prostředí, kde je limitovaná dostupná paměť (dostačuje 
k uložení seznamu) a je omezena dobou běhu. Implementovaná třída se nemusí zabývat 
kopírujícím konstruktorem ani přetěžováním operátoru =. V této úloze ProgTest neprovádí 
testy této funkčnosti.</p>

<p>Implementace třídy musí být efektivní z hlediska nároků na čas i nároků na paměť. 
Jednoduché lineární řešení nestačí (pro testovací data vyžaduje čas přes 5 minut). 
Předpokládejte, že vkládání a mazání zaměstnance jsou řádově méně časté než ostatní 
operace, tedy zde je lineární složitost akceptovatelná. Častá jsou volání 
<tt>getSalary</tt> a <tt>setSalary</tt>, jejich časová složitost musí být lepší než lineární 
(např. logaritmická nebo amortizovaná konstantní). Dále, metody
<tt>getFirst/getNext</tt> by též měly být efektivní, jejich složitost by též měla být lepší než lineární.</p>

<p>V povinných testech se metoda <tt>getRank</tt> volá málo často, tedy nemusí být příliš 
efektivní (pro úspěch v povinných testech stačí složitost lineární nebo <tt>n log n</tt>, 
pro bonusový test je potřeba složitost lepší než lineární. Pokud nechcete vymýšlet efektivní 
algoritmus pro bonusový test, zaměřte se spíše na to, aby volání <tt>setSalary</tt> byla 
efektivní i za cenu méně efektivní metody <tt>getRank</tt>.</p>

<p>Bonusový test lze vyřešit několika způsoby. Při návrhu řešení můžete využít znalosti, že 
zadávaná hodnota mzdy je nejvýše 1000000. Dále může pomoci znalost, že hodnoty mezd se 
často opakují.</p>

<p>Pro uložení hodnot alokujte pole dynamicky případně použijte STL. Pozor, 
pokud budete pole alokovat ve vlastní režii, zvolte počáteční velikost malou 
(např. tisíc prvků) a velikost zvětšujte/zmenšujte podle potřeby. Při zaplnění 
pole není vhodné alokovat nové pole větší pouze o jednu hodnotu, takový postup 
má obrovskou režii na kopírování obsahu. Je rozumné pole rozšiřovat s krokem 
řádově tisíců prvků, nebo geometrickou řadou s kvocientem ~1.5 až 2.</p>

<p>Pokud budete používat STL, nemusíte se starat o problémy s alokací. Pozor -
k dispozici máte pouze část STL (viz hlavičkové soubory v přiložené ukázce). Tedy 
například kontejnery <tt>map</tt> / <tt>unordered_map</tt> / <tt>set</tt> / 
<tt>unordered_set</tt> / ... nejsou k dispozici.</p>

<p>V přiloženém zdrojovém kódu jsou obsažené základní testy. Tyto testy zdaleka
nepokrývají všechny situace, pro odladění třídy je budete muset rozšířit. Upozorňujeme, 
že testy obsažené v odevzdaných zdrojových kódech považujeme za nedílnou součást 
Vašeho řešení. Pokud v odevzdaném řešení necháte cizí testy, může být práce 
vyhodnocena jako opsaná.</p>

<p>Správné řešení této úlohy, které splní závazné testy na 100%, může být 
odevzdáno k code review. (Tedy pro code review nemusíte zvládnout bonusové testy.)</p>
</td> 

</tr>
