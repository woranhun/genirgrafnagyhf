# Programozói Dokumentáció

# Programozói Dokumentáció

[TOC]

## Véglegesített osztályok

@image latex ./pics/UMLvegleges.png

![Vegleges UML](/home/woranhun/gitlab.bagaria/bme/prog2/genirgrafNagyHF/docs/pics/UMLvegleges.png)

Az elkészített program a fent látható osztályokat tartalmazza. A tervben szereplő UML diagramhoz képest néhány kisebb és 1 darab nagyobb változtatást tartalmaz. Ezen az ábrán már megtalálható egy Ember osztály is. Ez az osztályt a teszteléshez készítettem, ezért nem szerepelt még a tervben szereplő UML diagramban.

## A program részei

Részletes leírás a dokumentáció második felében található.

### graph.hpp

Ebben a fájlban található a gráfhoz és az azon végzek feladatok megvalósításához szükséges osztályok (`Graph` , `Graph< T >::VertexSet`, `Graph< T >::BFSSet`) és függvények.

### vertex.hpp

Ebben a fájlban található a csúcsokhoz tartozó (`Vertex`) osztály és annak függvényei.

### edge.hpp

Ebben a fájlban található az élekhez tartozó (`Edge`) osztály és annak függvényei.

### matrix.hpp

Ebben a fájlban található a mátrixhoz tartozó osztályok és annak függvényei.

A `Matrix` osztály egyik kulcsfontosságú eleme a kettős indexelés kényelmes működése. Ehhez a mátrixot két osztályra bontottam. Az első a `Matrix` osztály. Ez `MatrixRow<T>` elemeket tárol egy listában.  A második a `MatrixRow` osztály. Ez `T` -ket tárol egy listában. (Itt a T generikus adatot jelent) Ezzel a megközelítéssel a józan ész elvárásai szerint működik a kettős indexelés.

### ember.h

Ez a fájl az `Ember` osztályhoz tartozó header fájl.

### ember.cpp

Ez a fájl az `Ember` osztályhoz tartozó cpp fájl. Az ember osztály létezésének az oka részletesen a `Tesztesetek Dokumentációja`-ban található. 

## Memóriaszivárgás ellenőrzése

A program fejlesztése során felhasználtam a `memtrace` nevű programot, amelyet már korábban a laborok során használtam. Így végig ellenőrizni tudtam, hogy a programban nem található memóriaszivárgás.

## A program használata

A program használatára a ``Tesztesetek Dokumentációja`` -ban található részletes bemutató. Ezen felül a belső működés részletes leírása a dokumentáció végén található.



