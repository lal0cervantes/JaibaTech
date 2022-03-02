import pandas as pd
from colorama import Style, Back, Fore
import pyfiglet

archivo = pd.read_csv('synergy_logistics_database.csv', index_col='register_id')
exports =archivo[archivo['direction']=='Exports']
imports =archivo[archivo['direction']=='Imports']

#Colores
colorin = Fore.GREEN         #Color para Opciones principales
negrita = Style.BRIGHT       #Letras en Negrita
clr_reset = Style.RESET_ALL  #Restablecer efectos de color o letra
clr_tit = Fore.RED           #Color para titulo de opcion seleccionada
clr_sub = Fore.YELLOW        #Color para subopcion seleccionada
clr_ie = Fore.MAGENTA        #Color de opciones Importacion/Exportaciones
fneg = Fore.RED              #Color de letra de la etiqueta negada

#register_id,direction,origin,destination,year,date,product,transport_mode,company_name,total_value
def novalida(): #Mensaje de salida al insertar valor no valido
    print (fneg,"\n La opción NO es una opción valida, por favor intente nuevamente \n",clr_reset)
def opciones():  
    print(
clr_ie,'''
1) Exportaciones 
2) Importaciones'''
,clr_reset) 
def continuar(): #Funcion para detener el ciclo del programa 
    
    print(negrita,clr_tit,'¿Desea continuar?',clr_sub,'s/n',clr_reset)
    teclado= input()
    if teclado == 'y':
        pass
    elif teclado == 'n':
        print('Fue un placer ayudarle hoy ;)')
        exit()
def rfe(): #Fucion Rutas con mayor flujo en exportaciones
    exportaciones = archivo[archivo['direction'] =='Exports']
    rutas = exportaciones.groupby(['origin','destination'])
    top10 = rutas.count()['total_value'].sort_values(ascending=False).head(10).reset_index()
    print('Las 10 rutas con mayor flujo son:\n',top10.drop(['total_value'], axis=1))
def rfi(): #Fucion Rutas con mayor flujo en importaciones
    importaciones = archivo[archivo['direction'] =='Imports']
    rutas = importaciones.groupby(['origin','destination'])
    top10 = rutas.count()['total_value'].sort_values(ascending=False).head(10).reset_index()
    print('Las 10 rutas con mayor flujo son:\n',top10.drop(['total_value'], axis=1))
def mti_imp(): #Funcion medios de transporte importaciones
    freq = archivo[archivo['direction']=='Imports'].groupby(['transport_mode']).count() 
    #Determina el orden de la lista deacuerdo a la cantidad de veces que aparece y borra la columna direccion
    a=pd.DataFrame(freq.sort_values(by='direction', ascending=False).iloc[:, 0]).drop(['direction'], axis=1)
    #Convierte los valores de un Dataframe a una lista
    index_list = list(a.index.values)
    #Borra el 4to elemento de la lista
    index_list.pop(3)
    #Imprime los resultados en forma de lista
    for linea in index_list:
        print(linea)
def mti_exp(): #Funcion medios de transporte exportaciones
    freq = archivo[archivo['direction']=='Exports'].groupby(['transport_mode']).count() 
    #Determina el orden de la lista deacuerdo a la cantidad de veces que aparece y borra la columna direccion
    a=pd.DataFrame(freq.sort_values(by='direction', ascending=False).iloc[:, 0]).drop(['direction'], axis=1)
    #Convierte los valores de un Dataframe a una lista
    index_list = list(a.index.values)
    #Borra el 4to elemento de la lista
    index_list.pop(3)
    #Imprime los resultados en forma de lista
    for linea in index_list:
        print(linea)  

def pgg_exp(): #Paises que generan el 80% de las ganancias en exportaciones
    exportaciones = archivo[archivo['direction'] =='Exports']
    rutas = exportaciones.groupby(['origin','destination'])
    rutas_var = rutas.count()['total_value'].sort_values(ascending=False).reset_index()

    total=rutas_var['total_value'].sum()
    rutas_var['porcentaje']=rutas_var['total_value']/total*100
    rutas_var['por_acum']=rutas_var.cumsum()['porcentaje']
    top80 =rutas_var[rutas_var['por_acum']<80]
    print(top80.drop(['total_value','porcentaje','por_acum'], axis=1),'\n*Se muestran en un orden de ingresos.')
def pgg_imp(): #Paises que generan el 80% de las ganancias en importaciones
    importaciones = archivo[archivo['direction'] =='Imports']
    rutas = importaciones.groupby(['origin','destination'])
    rutas_var = rutas.count()['total_value'].sort_values(ascending=False).reset_index()

    total=rutas_var['total_value'].sum()
    rutas_var['porcentaje']=rutas_var['total_value']/total*100
    rutas_var['por_acum']=rutas_var.cumsum()['porcentaje']
    top80 =rutas_var[rutas_var['por_acum']<80]
    print(top80.drop(['total_value','porcentaje','por_acum'], axis=1),'\n*Se muestran en un orden de ingresos.')

def vtg_exp():  #Valor total de ganancias por año en exportaciones
    print('Se tuvo un total de: ',clr_tit,'{:,}'.format(exports.loc[exports['direction'] == 'Exports', 'total_value'].sum()),clr_reset, 'Pesos en ventas.')
def vtg_imp():  #Valor total de ganancias por año en importaciones
    print('Se tuvo un total de: ',clr_tit,'{:,}'.format(imports.loc[imports['direction'] == 'Imports', 'total_value'].sum()),clr_reset, 'Pesos en ventas.')
def salir():    #Función para salir el programa
    print('Fue un placer ayudarle hoy :)')
    exit()




print(pyfiglet.figlet_format("Synergy Logistics"))#Muestra en consola lo que escribas entre los parentesis pero en froma de un arte ASCII
while True:
    print(colorin,'\n     Opciones disponibles:',clr_reset,
'''
 1) 10 Rutas con mayor flujo.
 2) 3 Medios de transporte más importantes.
 3) Paises que generan el 80% de las ganancias.
 4) Valor total de ganancias por año.
Pulse la tecla (s) para salir del programa.
    ''')
    seleccion = input('Seleccione la opción que desea visualizar: ')
    if seleccion == '1':
        opciones()
        seleccion = input('Seleccione la opción que desea visualizar: ')
        if seleccion == '1':
            rfe()
            continuar()
            
        elif seleccion == '2':
            rfi()
            continuar()
        else:
            novalida()
       
    elif seleccion == '2':
        opciones()
        seleccion = input('Seleccione la opción que desea visualizar: ')
        if seleccion == '1':
            mti_exp()
        
            continuar()
        elif seleccion == '2':
            mti_imp()
            
            continuar()
        else:
            novalida()
          
    elif seleccion == '3':
        opciones()
        seleccion = input('Seleccione la opción que desea visualizar: ')
        if seleccion == '1':
            pgg_exp()
            continuar()
        elif seleccion == '2':
            pgg_imp()
            continuar()
        else:
            novalida()
          
    elif seleccion == '4':
        opciones()
        seleccion = input('Seleccione la opción que desea visualizar: ')
        if seleccion == '1':
            vtg_exp()
            continuar()
        elif seleccion == '2':
            vtg_imp()
            continuar()
        else:
            novalida()
           
    elif seleccion == 's': #Ejecuta función para salir del ciclo while
        salir()    
    else:
        novalida()  #invoca mensaje de entrada de teclado no valida
