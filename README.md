# 2-as laboratorinis darbas: Perrinkimo algoritmai

## Varianto sąlyga (Variantas 5)
Išdėstyti šachmatų lentoje 5 karalienes taip, kad kiekvienas langelis būtų kontroliuojamas bent vienos iš jų. Tyrimas atliekamas su trijų dydžių lentomis: $N=8$, $N=7$ ir $N=9$.

## Bendroji kompetencija: Bendravimas ir bendradarbiavimas
[Čia aprašykite, kaip bendravote su kolegomis ar dėstytoju, kaip dalinotės informacija apie algoritmą ar testavimo rezultatus, užtikrinant bendrą darbo sėkmę].

## Algoritmo aprašymas
Programa naudoja perrinkimo (backtracking) metodą. 
* **Režimai**: Palaikomi `fullSearch`, `firstMatchSearch` ir `heuristic` režimai per komandinę eilutę.
* **Euristika**: [nurodykite šaltinį ir veikimo principą be tuščiažodžiavimo].


Usage:
```
main.exe [-|failo_vardas] [-mode [fullSearch|firstMatchSearch|heuristic heuristic_number]] [-timeout miliseconds]
```