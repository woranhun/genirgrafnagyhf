# Generikus irányítatlan gráf specifikáció

[TOC]

## Feladatkiírás

Készítsen generikus irányítatlan gráfot! A gráf megadása szomszédsági mátrixszal történjen! A csomópontokat osztállyal reprezentálja!  Definiáljon műveleteket annak meghatározására, hogy a gráfnak hány  csomópontja és hány éle van! Szélességi bejárással állapítsa meg, hogy a gráf összefüggő-e!
Demonstrálja a működést külön modulként fordított tesztprogrammal! A megoldáshoz **ne** használjon STL tárolót!

## Bevezetés

A program elsődleges célja generikus irányítatlan gráfok tárolása és ezekkel történő műveletek végzése.  Ezen felül nyújtson segítséget a BSZ2 tárgynak a feladatkiírásban szereplő részeinek a mélyebb megértésében és az ehhez kapcsolódó feladatok ellenőrzésében.

## A program képességei

A gráf kifejezés alatt mindenhol egy n csúcsú és e élű irányítatlan egyszerű G gráfot értek.

- Gráfok eltárolása a programban
  - Szomszédsági mátrix beolvasása fájlból.
  - Szomszédsági mátrix kiírása fájlba.
  - Szomszédsági mátrix megjelenítése a standard outputon.
- Műveletek gráfokkal
  - Csomópont szám meghatározása
  - Élszám meghatározása
  - Gráf összefüggőségének vizsgálata
- Tesztprogram
  - A Programhoz tartozik tesztprogram is, ami a fenti képességek helyességét ellenőrzi.

## Gráfok eltárolása

A program legyen képes olyan módon gráfokat tárolni, amely lehetővé teszi a műveletvégzést.

### Gráfok beolvasása

A gráf megadása egy M szomszédsági mátrixszal történik. Az M mátrix n x n-es méretű. Az M mátrix a<sub>1,2</sub>

eleme 1, ha a 1-es és 2-es indexű csúcsok között él húzódik és 0, ha nem. A csúcsok tetszőleges típusú adatokat tartalmazhatnak.

```
n 
a1, a2, a3, a4 ... an
b1, b2, b3, b4 ... bn
.	.	.	.		.
.	.	.	.		.
.	.	.	.		.
n1, n2, n3, n4 ... nn
```

Minden T típusú adathoz létezik egy függvény, ami elvégzi annak az adatnak a beolvasását. Ennek az elkészítése és a helyesség biztosítása a felhasználó dolga.

### Gráfok kiírása

A gráf kiírása a bemenethez hasonló szomszédsági mátrixszal történik. 

## Gráf összefüggőségének vizsgálata

A feladat megvalósításához a program a BSZ2 tárgy során tanult BFS algoritmust fogja használni.





