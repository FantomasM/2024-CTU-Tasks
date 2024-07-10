<td class="header"><b>Kontrola kontrolního hlášení</b></td>

<td class="lrtbCell" colspan="3" align="left"><p>Úkolem je realizovat třídy, které implementují správu daně z přidané hodnoty.</p>

<p>Předpokládáme, že firmy si předávají faktury. Firma, která vydá fakturu, musí z fakturované 
částky odvést státu DPH. Analogicky, firma, která přijme (a zaplatí fakturu) může po státu 
nárokovat vratku DPH (za určitých okolností). Právě vracení DPH je slabým místem, které lze využít ke 
krácení daně a daňovým podvodům. Proto je úkolem implementovat jádro systému, který bude takové 
krácení daně ztěžovat.</p>

<p>Vydané a přijaté faktury eviduje třída <tt>CVATRegister</tt>. Firmy musí registrovat vydávané 
a přijímané faktury. Registr páruje dvojice sobě odpovídajících faktur a je schopen najít faktury 
nespárované. Fakturu lze do registru jednak přidat a dále i zrušit (např. při chybně zadaných údajích).
Rozhraní třídy je následující:</p>

<dl>
  <dt>implicitní konstruktor</dt><dd>inicializuje prázdnou instanci registru,</dd>
  
  <dt>registerCompany ( name )</dt><dd>metoda zavede zadanou firmu do registru. Předané jméno je 
    oficiální název firmy, toto jméno bude používané v exportech z registru. Návratovou hodnotou 
    je indikátor úspěchu (<tt>true</tt>)/neúspěchu (<tt>false</tt>). Za neúspěch považujte, pokud 
    v registru již existuje firma stejného jména. Při porovnávání jména firmy je registr docela 
    tolerantní:
    <ul>
      <li>při porovnávání nerozlišuje malá a velká písmena,</li>
      <li>při porovnávání neuvažuje nadbytečné mezery.</li>
    </ul>
    Tato pravidla jsou používána při zakládání nové firmy i vkládání / mazání faktur. Například
    názvy "My Company", "mY CoMpAnY", "  My    Company    " a " mY   CoMPAnY " jsou považované za 
    jednu firmu, ale názvy "My Company" a "MyCompany"  označují dvě rozdílné firmy.</dd>


  <dt>addIssued ( invoice )</dt><dd>metoda přidá fakturu do registru. Tuto metodu volá firma, 
    která fakturu vydala. Návratovou hodnotou je příznak úspěch (<tt>true</tt>)/neúspěch (<tt>false</tt>).
    Za chybu je považováno, pokud prodávající / kupující ve faktuře nejsou registrované, prodávající a 
    kupující je ta samá firma nebo pokud stejná faktura již byla pomocí <tt>addIssued</tt> zadaná 
    (dvě faktury se musí lišit alespoň v jednom z: prodávající/kupující/datum/částka/DPH).</dd>
    
  <dt>addAccepted ( invoice )</dt><dd>metoda přidá fakturu do registru, tuto metodu volá firma, která fakturu
    přijala (kupující). Jinak se metoda chová stejně jako <tt>addIssued</tt>.</dd>

  <dt>delIssued ( invoice )</dt><dd>metoda odebere fakturu z registru. Tuto metodu volá firma, 
    která fakturu vydala a dříve zaregistrovala. Návratovou hodnotou je příznak úspěch (<tt>true</tt>)/neúspěch (<tt>false</tt>).
    Za chybu je považováno, pokud identická faktura nebyla dříve registrovaná metodou <tt>addIssued</tt>.</dd>
    
  <dt>delAccepted ( invoice )</dt><dd>metoda odebere fakturu z registru. Tuto metodu volá firma, 
    která fakturu přijala a dříve zaregistrovala. Návratovou hodnotou je příznak úspěch (<tt>true</tt>)/neúspěch (<tt>false</tt>).
    Za chybu je považováno, pokud identická faktura nebyla dříve registrovaná metodou <tt>addAccepted</tt>.</dd>

  <dt>unmatched ( company, sortOpt )</dt><dd>metoda nalezne všechny faktury, které se týkají zadané firmy 
    <tt>company</tt> a nebyly spárované (tedy byly registrované pouze pomocí addIssued nebo pouze pomocí 
    addAccepted). Metoda vrátí seznam těchto faktur, faktury budou seřazené podle kritérií udaných 
    <tt>sortOpt</tt>. Faktury vrácené touto metodou budou mít na místě názvu firmy "oficiální" název, 
    tedy ten název, který byl zadán při registraci firmy metodou <tt>registerCompany</tt>. Tento oficiální 
    název bude rovněž použit při řazení.</dd>
</dl>

<p>Třída <tt>CInvoice</tt> reprezentuje jednu fakturu. Rozhraní musí splňovat:</p>
<dl>
 <dt>konstruktor ( date, seller, buyer, amount, vat )</dt><dd>inicializace fakturu datem, jménem prodávající a 
   kupující firmy, fakturovanou částkou a DPH.</dd>
 <dt>date, seller, buyer, amount, vat</dt><dd>přístupové metody ke čtení jednotlivých složek faktury.</dd>
 <dt>další</dt><dd>do rozhraní faktury si můžete doplnit další veřejné/neveřejné metody a členské proměnné, 
  které pro implementaci budete potřebovat.</dd>
</dl>

<p>Třída <tt>CSortOpt</tt> určuje kritéria pro řazení. Pro řazení lze použít všechny složky faktury. 
Pokud například vytvoříme instanci: 

<pre>CSortOpt () . addKey ( CSortOpt::BY_AMOUNT, true ) . addKey ( CSortOpt::BY_SELLER, false )</pre>

pak se řadí podle fakturované částky vzestupně (první řadicí kritérium) a pro stejné hodnoty fakturované částky 
se použije řazení podle jména prodávajícího sestupně (druhé řadicí kritérium). Pokud by ani takto nebylo pořadí 
jednoznačně určené, použije se jako řadicí kritérium pořadí zavedení faktury do registru. Rozhraní třídy <tt>CSortOpt</tt> je:</p>

<dl>
 <dt>implicitní konstruktor</dt><dd>inicializuje prázdnou instanci třídy</dd>
 <dt>addKey ( sortBy, ascending )</dt><dd>přidá další řadicí kritérium <tt>sortBy</tt>, směr řazení je daný příznakem 
   <tt>ascending</tt> (<tt>true</tt> = vzestupně, <tt>false</tt> = sestupně). Řadit lze podle:
   <ul>
    <li><tt>BY_DATE</tt> - podle data faktury,</li>
    <li><tt>BY_SELLER</tt> - podle oficiálního jména prodávající firmy, řadí se bez ohledu na malá/velká písmena,</li>
    <li><tt>BY_BUYER</tt> - podle oficiálního jména kupující firmy, řadí se bez ohledu na malá/velká písmena,</li>
    <li><tt>BY_AMOUNT</tt> - podle fakturované částky,</li>
    <li><tt>BY_VAT</tt> - podle DPH</li>
   </ul></dd>
</dl>

<p>Třída <tt>CDate</tt> implementuje jednoduché datum, její implementace je hotová v testovacím prostředí 
a pro testování ji máte dodanou v přiloženém archivu. Její implementaci nelze měnit, dodaná implementace 
musí zůstat v bloku podmíněného překladu.</p>
  
<p>Odevzdávejte zdrojový kód s implementací tříd <tt>CVATRegister</tt>, <tt>CInvoice</tt> a <tt>CSortOpt</tt>. 
Za základ implementace použijte přiložený soubor s deklarací metod a se sadou základních testů. Pro implementaci 
se může hodit doplnit i další pomocné třídy.</p>

<p>Zadání se trochu podobá dřívější domácí úloze. Předpokládáme, že při implementaci použijete vhodné kontejnery 
z STL (je k dispozici téměř celá), dále předpokládáme, že Vaše implementace bude časově a paměťově efektivní.
Veškeré vkládání a mazání by mělo být rychlejší než lineární, řazení pak <tt>n log n</tt> (<tt>n</tt> je velikost 
vraceného seznamu). Není rozumné na všechny vnitřní struktury používat kolekci <tt>vector</tt>. Pokud chcete využívat C++11 
kontejnery <tt>unordered_set / unordered_map</tt>, pak hashovací funktor neodvozujte jako specializaci 
<tt>std::hash</tt>. Hashovací funkci/funktor deklarujte explicitně při vytváření instance 
<tt>unordered_set / unordered_map</tt>. (Specializace <tt>std::hash</tt> předpokládá opětovné otevření 
jmenného prostoru <tt>std</tt>. To se těžko realizuje, pokud jste uzavřeni do jiného jmenného prostoru. 
Návody dostupné na internetu (stack overflow, cpp reference) implicitně předpokládají, že jmenné prostory 
nepoužíváte, na nich doporučovaná řešení nejsou univerzálně použitelná.</p>

<p>Správné řešení této úlohy, které splní závazné testy na 100%, může být 
odevzdáno k code review. (Tedy pro code review nemusíte zvládnout bonusové testy.)</p>
</td> 

</tr>
