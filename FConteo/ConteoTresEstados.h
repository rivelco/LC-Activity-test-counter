// Realiza el conteo estándar con dos estados

void ConteoTresEstados(){
	Cabecera("Perform a register");

	// Variables para medir el tiempo
	li freq, t1, t2;
	int i; // Para el ciclo
	
	// Caracter de apoyo, será las entradas del usuario
	char letra;
	
	// Mensaje al usuario de espera
	InfoGrlRegistro();
	for (int j=0; j<100000; j++){
		registro[0][j] = 0;
		registro[1][j] = 0;
	}
	cout << "    Press a key according to the location of the animal" << endl
		 << "       " << PMOpen << " -> For open spaces" << endl
		 << "       " << PMCenter << " -> For central space" << endl
		 << "       " << PMClose << " -> For closed spaces" << endl
		 << endl
		 << "    You will get a visual confirmation in a color code" << endl
		 << "       Green font  -> open space" << endl
		 << "       Yellow font -> central space" << endl
		 << "       Red font    -> closed space" << endl
		 << endl
		 << "    When you want to finish the register press: " << CharSalida << endl
		 << endl
		 << "    Waiting for the start of the register ...";
	RegNombre.insert(0, RutaRegistro);

	// Obtenemos la frecuencia
	QueryPerformanceFrequency(&freq);
	
	// Comienza a contar en cuanto se reciba entrada
	letra = getch();
	
	// Mensaje al usuario de grabación
	cout << "\n    Registering ...\n    ";
	
	// Mientras no excedamos 100000 entradas y no ingresemos el caracter de fin
	for (i=0; letra != CharSalida && i < 100000; i++){
		if (letra == PMOpen){
			registro[0][i] = 0;
			system("color 0a");
		} else if (letra == PMCenter){
			registro[0][i] = 1;
			system("color 0e");
		} else if (letra == PMClose){
			registro[0][i] = 2;
			system("color 0c");
		} else {
			cout << "\n    Correction\n";
			registro[0][i] = i > 0 ? registro[0][i-1] : 1;
		}
		QueryPerformanceCounter(&t1);		// Definimos el t1
		letra = getch();					// En espera de presionar el botón
		QueryPerformanceCounter(&t2);		// Definimos el t2
		// Calculamos la diferencia de tiempos, en milisegundos y según la frecuencia
		registro[1][i] = (t2.QuadPart - t1.QuadPart) * 1000.0 / freq.QuadPart;
	}
	system("color 07");		// Regresamos al blanco y negro

	// Determinamos la cantidad de cambios de estado
	TiemposCont = i;
	
	// Mensaje al usuario de fin del conteo
	cout << endl << "    End of the register" << endl << endl;
	return;
}