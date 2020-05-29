# Tesztesetek Dokumentációja
# Tesztesetek Dokumentációja

[TOC]

## Az Ember osztály

A tesztekhez létrehoztam egy `Ember` osztályt, ami tetszőlegesen kicserélhető bármilyen másik osztályra is. Az `Ember` osztály két változót tartalmaz.  Egy `nev` és egy `kor`. Ezekben az emberek nevét és életkorát tárolom. Ezenkívül tartalmaz az osztály még néhány alapvető függvényt is. Az osztály részletesebb leírása megtalálható a Dokumentáció második felében.

## A main-ben található tesztesetek

A main függvényben összesen 4 db fő tesztet készítettem el. Ebből az utolsó két teszteset  két darab alrészből áll.

### Teszt 1

Az első teszt a fájlból történő beolvasás és az oda történő kiírás ellenőrzését szolgálja. Miután lefutott létrejön `g1save.txt` nevű fájl, aminek a tartalma megegyezik a `g1f.txt` tartalmával.  Ezzel ellenőriztük, hogy a fájlba írás és onnan olvasás megfelelően működik. A konzolon megjelennek a gráfhoz tartozó adatok is ezzel ez a rész is ellenőrzésre került.

```c++
    std::ifstream t1f("g1f.txt");
    std::ifstream t1fdata("g1data.txt");
    Graph<Ember> t1(t1f);
    t1.readDataFromFile(t1fdata,Ember::CreateEmber);
    t1.saveAdjMatrixToFile("g1save.txt");
    std::cout << t1;
```

### Teszt 2

A második teszt arra szolgál, hogy ellenőrizzük, hogy az elkészült osztály generikus-e. Itt az `Ember` után `char` típussal hozom létre a gráfot. Itt a konzolon megjelennek a `char` típusú adatok ebből tudjuk, hogy ez is jól működik.

```cpp
std::ifstream t2f("g2f.txt");
std::ifstream t2fdata("g2fdata.txt");
Graph<char> t2(t2f);
t2.readDataFromFile(t2fdata);
std::cout << t2;
```

### Teszt 3

A harmadik tesztben a gráfon lefuttatok egy BFS algoritmust. Itt a konzolon megjelennek az algoritmus által bejárt csúcsok. Ebből tudjuk, hogy ez is jól működik.

```cpp
    std::ifstream t3f("g5f.txt");
    Graph<char> t3(t3f);
    Graph<char>::BFSSet *ret = t3.BFS(4);
    std::cout << t3;
    std::cout << *ret;
    delete ret
```



### Teszt 4

A negyedik tesztben az összefüggőségi vizsgálatot végzem el. Az A részben a gráf összefüggő a B részben nem. A B részben található gráf nagy mértékben hasonlít az A részben láthatóhoz. A fő különbség annyi, hogy a B gráfban a 0-ás és 1-es csúcs csak egymással vannak összekötve, ezért a gráfnak legalább 2 db komponense van, tehát nem lesz összefüggő.

#### A rész

Itt a konzolon megjelenő 1-es szám jelzi számunkra, hogy a gráf összefüggő.

```cpp
    std::ifstream t4af("g6af.txt");
    std::ifstream t4afdata("g6bdata.txt");
    Graph<Ember> t4a(t4af);
    t4a.readDataFromFile(t4afdata,Ember::CreateEmber);
    std::cout << t4a;
    std::cout << t4a.isConnectedGraph() << std::endl;
```



#### B rész

Itt a konzolon megjelenő 0-ás szám jelzi, hogy a gráf nem összefüggő. 

```cpp
    std::ifstream t4bf("g6bf.txt");
    std::ifstream t4bfdata("g6bdata.txt");
    Graph<Ember> t4b(t4bf);
    t4b.readDataFromFile(t4bfdata,Ember::CreateEmber);
    std::cout << t4b;
    std::cout << t4b.isConnectedGraph() << std::endl;
```

Összességében úgy gondolom, hogy ezekkel a tesztekkel lefedtem a programot, azok alapján a szempontok alapján, amit a specifikációban rögzítettem. 