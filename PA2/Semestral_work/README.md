<td class="header"><b>Hra: Textové RPG (Gamebook)</b></td>

<td class="lrtbCell" colspan="3" align="left"><div class="paragraph">
<p><em>Tato semestrální práce patří do kategorie <strong>her</strong>. Vaším cílem je vytvořit engine pro hru, nikoli konkrétní hru (příběh). Engine bude umožňovat definovat hru (příběh) prostřednictvím konfiguračních souborů. Nesnažte se definovat všechny části v kódu (a to ani pomocí konstant). Umístěte je do konfiguračních souborů (jednoho nebo více), které váš program bude načítat.</em></p>
</div>
<div class="paragraph">
<p>Vaším cílem je naprogramuovat engine pro textové RPG (<em>gamebook</em>), nesnažte se přímo ve vašem kódu implementovat třídy pro konkrétní příběh. Ten je definován v konfiguračních souborech a mělo by tak být jednoduché změnit "souboj s nejvyšším elfem" za "posezení na kávě s vesmírným slimákem". Textové RPG funguje na principu jednotlivých dialogů, kdy vám je aktuální prostředí textově popsáno (takzvaná místnost) a následně nabídnuto několik akcí, které se dají provést, nebo přejít do nějaké "sousední místnosti".</p>
</div>
<div class="paragraph">
<p>Váš engine musí implementovat následující funkcionality:</p>
</div>
<div class="olist arabic">
<ol class="arabic">
<li>
<p>Umožněte vytvořit herní postavu, kde si uživatel může</p>
<div class="olist loweralpha">
<ol class="loweralpha" type="a">
<li>
<p>navolit alespoň 3 různé druhy atributů (př. síla, obratnost, inteligence, …),</p>
</li>
<li>
<p>vybrat schopnost/i nebo povolání (př. válečník, lučištník, mág, …).</p>
</li>
</ol>
</div>
</li>
<li>
<p>Každá schopnost (povolání) může mít více efektů, které mohou být aktivní (uživatel je musí použít) nebo pasivní (jsou aktivovány automaticky).</p>
</li>
<li>
<p>Interakce se světem probíhá pomocí textového popisu jednotlivých místností a zadáváním akcí prostřednictvím klávesnice (př. volba akce z předem definované nabídky, klíčová slova ala Zork nebo Albion, …).</p>
</li>
<li>
<p>Implementujte jednoduchý soubojový systém a inventář</p>
</li>
<li>
<p>Hra musí být konfigurovatelná ze souboru:</p>
<div class="olist loweralpha">
<ol class="loweralpha" type="a">
<li>
<p>definice atributů (př. název, …) a schopností/povolání (př. název, cena, efekty, …)</p>
</li>
<li>
<p>definice světa (př. místnosti, předměty, příšery, dialogy, cíl, …)</p>
</li>
</ol>
</div>
</li>
<li>
<p>Hra musí umožnit uložit a následně načíst rozehranou hru.</p>
</li>
</ol>
</div>
<div class="paragraph">
<p>Kde lze využít polymorfismus? <em>(doporučené)</em></p>
</div>
<div class="ulist">
<ul>
<li>
<p>soubojové entity: postava, příšera, stroj (př. past, bomba, …)</p>
</li>
<li>
<p>efekty schopností/povolání: válečník (útočí dvakrát za kolo), lučištník (může střílet na větší vzdálenost), mág (nižší síla, ale každé kolo automaticky zraňuje nepřátele v dosahu), … <em>(jde o efekty těchto schopnosti/povolání, které se dají kombinovat, nikoli o schopnosti/povolání samotné)</em></p>
</li>
<li>
<p>efekty akcí: souboje, události (pád ze stromu, …), přechod do jiné místnosti, …</p>
</li>
<li>
<p>inventář: postava (ruce, pouze 2 věci + brnění), batoh (nosnost), toulec (pouze šípy), kapsy (pouze malé věci), …</p>
</li>
<li>
<p>uživatelské rozhraní: konzole, ncurses, SDL (ke každé místnosti může být obrázek, souboje můžou být vizualizované), OpenGL (různé varianty), …</p>
</li>
</ul>
</div>
<div class="paragraph">
<p>Další informace:</p>
</div>
<div class="ulist">
<ul>
<li>
<p><a href="https://cs.wikipedia.org/wiki/Gamebook" class="bare">https://cs.wikipedia.org/wiki/Gamebook</a></p>
</li>
<li>
<p><a href="https://www.projectaon.org/en/Main/Books" class="bare">https://www.projectaon.org/en/Main/Books</a></p>
</li>
<li>
<p><a href="http://www.drd2.cz/" class="bare">http://www.drd2.cz/</a></p>
</li>
<li>
<p>Dungeons &amp; Dragons</p>
</li>
</ul>
</div></td> 

</tr>
