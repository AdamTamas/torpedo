# torpedo
Szakdoga

windeployqt	-- ha egy olyan mappában van futtatva ahol csak az exe van akkor belemásol minden dependencyt

- Ctrl+n - játékbeállítás ablak megnyitása,
- Ctrl+c - online játékhoz történő csatlakozás,
- Ctrl+u - online játékhoz chat előhozása

Ismert bugok: 
- Ha túl sok halyó van felrakva kifagy, (egy hajószámolás kell vagy beállítani a minimum méretet nagyobbra mint 5x5)
- Ha hajófelrakás menüben a hajó kék mikor bezárjuk akkor a hajó "eltűnik", (Ha bezárjuk a tfelrakás menüt akkor le kell futtatni egy ellenörzőt és visszarakni a felvett hajót ha még kézben van tartva)
- Hajófelrakás közben már lőhető a játéktábla -> Javítva, mainWindow mostmár nem elérhető miközben hajót rakunk fel.

online játék bugjai:
- új játéknál hamarabb tudunk lőni minthogy a másik játékos készen állna, emiatt befagy a játék (várni kell egy IAmReady adatra a connectiönnél) -> javítva
- ha connectelünk akkor fentmarad a board miközben a saját táblánkat felrakjuk (connectnél is el kell rejteni a boardot) -> javítva
- játék végeztével csak random pályánk lehet (új játék indulésakor fel kell hozni a pályamódosítót) -> javítva
- ha csatlakoztunk szerverhez nem tudunk máshoz csatlakozni/újracsatlakozni -> javítva
- felcsatlakozó játékosnál a hajófelrakó ablak először a régi data táblával jelenik meg  -> javítva
