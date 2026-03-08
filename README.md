# 2-as laboratorinis darbas

## Varianto sąlyga (Variantas 5)
Išdėstyti šachmatų lentoje 5 karalienes taip, kad kiekvienas langelis būtų kontroliuojamas bent vienos iš jų. Tyrimas atliekamas su trijų dydžių lentomis: $N=8$, $N=7$ ir $N=9$.

## Algoritmo aprašymas
Programa naudoja perrinkimo (backtracking) metodą. 
* **Režimai**: Palaikomi `fullSearch` ir `firstMatchSearch` režimai per komandinę eilutę.


Usage:
```
main.exe [-|failo_vardas] [-mode [fullSearch|firstMatchSearch|heuristic heuristic_number]] [-desk_size cells_number] [-timeout miliseconds] [-o_format [html|cmd]]
```