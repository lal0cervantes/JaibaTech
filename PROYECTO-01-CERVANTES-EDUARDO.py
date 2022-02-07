from lifestore_file import lifestore_searches, lifestore_sales, lifestore_products
import collections
from colorama import Style, Back, Fore
import getpass

usuario = 'jimmy'           #Especifique el usuario
contrasena =  'ymmij'       #Especifique la contraseña
intentos_permitidos= 3      #Especifique la cantidad de intentos que permitirá


#Colores
colorin = Fore.GREEN         #Color para Login
negrita = Style.BRIGHT       #Letras en Negrita
clr_reset = Style.RESET_ALL  #Restablecer efectos de color o letra
clr_username = Fore.CYAN     #Color para Usuario
clr_tit = Fore.RED           #Color para titulo de opcion seleccionada
clr_sub = Fore.MAGENTA       #Color para subopcion seleccionada
clr_mes = Fore.GREEN         #Color del mes de venta
clr_monto = Fore.RED         #Color de la cantidad vendida
clr_items = Fore.CYAN        #Color del # de items vendidos
backneg = Back.YELLOW        #Color de fondo de etiqueta
fneg = Fore.RED              #Color de letra de la etiqueta negada


estado = False
intentos = 0


while (estado == False and intentos <intentos_permitidos):    #Función de bucle para inicio de sesión
    print('\n Número de intentos disponibles:', (intentos_permitidos-intentos), '\n')
    username_input = input(colorin + negrita + 'Ingrese usuario:'+clr_reset)
    password_input = input(colorin + negrita +'Ingrese contraseña:'+clr_reset)
    #Descomentar la linea inferior y comentar la linea anterior en caso de que no desee que se muestre en consola cuando se teclee la contraseña
    #password_input = getpass.getpass(colorin + negrita +'Ingrese contraseña:'+clr_reset)
    
    intentos = intentos +1 
    
    if username_input == usuario and password_input == contrasena:
        estado = True
    elif username_input != usuario:
        print(negrita+'Usuario NO encontrado'+clr_reset)
        estado =False
    elif username_input == usuario and password_input != contrasena:
        print(negrita+'La contraseña es incorrecta'+clr_reset)
        estado =False
    
    
    
if estado == True:      #Función en caso de acreditar el inicio de sesión

    print('Bienvenido de nuevo'+ clr_username,  usuario + clr_reset +', selecciona la opción que deseas visualizar:' +'''
\n
  1) Productos más vendidos y productos rezagados.
  2) Productos por reseña en el servicio.
  3) Total de ingresos
  ''')
  
    seleccion = input('Seleccione la opción que desea visualizar: ')
    
    if seleccion == '1':    #Productos más vendidos y productos rezagados
        print(
'Opción seleccionada:' + clr_tit +" Productos más vendidos y productos rezagados."+clr_reset+'''
\n
  1) Producto más vendido.
  2) Top 5 de Productos más vendidos.
  3) Top 5 de Productos menos vendidos.
  4) Top 10 de Productos más buscados.
  5) Top 10 de Productos menos buscados.

          ''')
        seleccion = input('Seleccione la opción que desea visualizar:')

        if seleccion   =='1': # Articulo más vendido
            print(clr_sub+'Productos más vendido'+clr_reset)
            from statistics import mode

            prod_compr =[]
            for i in range(len(prod_compr)):
                prod_compr[i] = int(prod_compr[i])
            for val in lifestore_sales:
                prod_compr.append(val[1])  
            print(lifestore_products[mode(prod_compr) -1][1]) 

        elif seleccion =='2': # 5 Productos más vendidos
            print(clr_sub+' 5 Productos más vendidos: \n'+ clr_reset)
            prod_compr =[]
            for val in lifestore_sales: #Funcion para definir un listado de las ventas
                prod_compr.append(val[1])
            repeticiones = {}

            for n in prod_compr:
                if n in repeticiones :
                    repeticiones[n] += 1
                else:
                    repeticiones[n] = 0
            primero = (collections.Counter(repeticiones).most_common()[0][0])-1
            segundo = (collections.Counter(repeticiones).most_common()[1][0])-1
            tercero = (collections.Counter(repeticiones).most_common()[2][0])-1
            cuarto = (collections.Counter(repeticiones).most_common()[3][0])-1
            quinto = (collections.Counter(repeticiones).most_common()[4][0])-1
            print('\n',
lifestore_products[primero][1],'\n',
lifestore_products[segundo][1],'\n',
lifestore_products[tercero][1],'\n',
lifestore_products[cuarto][1],'\n',
lifestore_products[quinto][1],'\n',
            )
    
        elif seleccion =='3': # 5 Productos menos vendidos
            print(clr_sub+'5 Productos menos vendidos.\n'+clr_reset)
            prod_compr =[]
            for val in lifestore_sales: #Funcion para definir un listado de las ventas
                prod_compr.append(val[1])
            repeticiones = {}

            for n in prod_compr:
                if n in repeticiones :
                    repeticiones[n] += 1
                else:
                    repeticiones[n] = 0
            primero1 = collections.Counter(repeticiones).most_common()[-1][0]-1
            segundo1 = collections.Counter(repeticiones).most_common()[-2][0]-1
            tercero1 = collections.Counter(repeticiones).most_common()[-3][0]-1
            cuarto1 = collections.Counter(repeticiones).most_common()[-4][0]-1
            quinto1 = collections.Counter(repeticiones).most_common()[-5][0]-1
            print('\n',
lifestore_products[primero1][1],'\n',
lifestore_products[segundo1][1],'\n',
lifestore_products[tercero1][1],'\n',
lifestore_products[cuarto1][1],'\n',
lifestore_products[quinto1][1],'\n'
            )
                           
        elif seleccion =='4': #10 Productos más buscados
            print(clr_sub+'10 Productos más buscados \n'+clr_reset)
            busquedas =[]
            for val in lifestore_searches: #Funcion para definir un listado de las ventas
                busquedas.append(val[1])  
            repeticiones = {}

            for n in busquedas:
                if n in repeticiones :
                    repeticiones[n] += 1
                else:
                    repeticiones[n] = 0
            primero = (collections.Counter(repeticiones).most_common()[0][0])-1
            segundo = (collections.Counter(repeticiones).most_common()[1][0])-1
            tercero = (collections.Counter(repeticiones).most_common()[2][0])-1
            cuarto = (collections.Counter(repeticiones).most_common()[3][0])-1
            quinto = (collections.Counter(repeticiones).most_common()[4][0])-1
            sexto = (collections.Counter(repeticiones).most_common()[5][0])-1
            septimo = (collections.Counter(repeticiones).most_common()[6][0])-1
            octavo = (collections.Counter(repeticiones).most_common()[7][0])-1
            noveno = (collections.Counter(repeticiones).most_common()[8][0])-1
            decimo = (collections.Counter(repeticiones).most_common()[9][0])-1
            print('\n',
lifestore_products[primero][1],'\n',
lifestore_products[segundo][1],'\n',
lifestore_products[tercero][1],'\n',
lifestore_products[cuarto][1],'\n',
lifestore_products[quinto][1],'\n',
lifestore_products[sexto][1],'\n',
lifestore_products[septimo][1],'\n',
lifestore_products[octavo][1],'\n',
lifestore_products[noveno][1],'\n',
lifestore_products[decimo][1],'\n'
            )
        
        elif seleccion =='5': #10 Productos menos buscados
            print(clr_sub+'10 Productos menos buscados. \n '+clr_reset)
            busquedas =[]
            for val in lifestore_searches: #Funcion para definir un listado de las ventas
                busquedas.append(val[1])  
            repeticiones = {}

            for n in busquedas:
                if n in repeticiones :
                    repeticiones[n] += 1
                else:
                    repeticiones[n] = 0
            primero = (collections.Counter(repeticiones).most_common()[-1][0])-1
            segundo = (collections.Counter(repeticiones).most_common()[-2][0])-1
            tercero = (collections.Counter(repeticiones).most_common()[-3][0])-1
            cuarto = (collections.Counter(repeticiones).most_common()[-4][0])-1
            quinto = (collections.Counter(repeticiones).most_common()[-5][0])-1
            sexto = (collections.Counter(repeticiones).most_common()[-6][0])-1
            septimo = (collections.Counter(repeticiones).most_common()[-7][0])-1
            octavo = (collections.Counter(repeticiones).most_common()[-8][0])-1
            noveno = (collections.Counter(repeticiones).most_common()[-9][0])-1
            decimo = (collections.Counter(repeticiones).most_common()[-10][0])-1
            print('\n',
lifestore_products[primero][1],'\n',
lifestore_products[segundo][1],'\n',
lifestore_products[tercero][1],'\n',
lifestore_products[cuarto][1],'\n',
lifestore_products[quinto][1],'\n',
lifestore_products[sexto][1],'\n',
lifestore_products[septimo][1],'\n',
lifestore_products[octavo][1],'\n',
lifestore_products[noveno][1],'\n',
lifestore_products[decimo][1],'\n'
            )
          
        else:
            print(negrita+'La funcion:', seleccion, 'no es válida.'+clr_reset) 
    
    elif seleccion == '2':  #Productos por reseña en el servicio
        print( 
'Opción seleccionada:'+ clr_tit + "Productos por reseña en el servicio."+ clr_reset +'''\n
  1) Top 5 con mejores reseñas
  2) Top 5 con las peores reseñas
''')
        seleccion = input('Seleccione la opción que desea visualizar: ')
        if seleccion =='1': #Productos con mejores reseñas
            print(clr_sub+'Productos con mejores reseñas'+ clr_reset)
            def merge(resenas, id_producto):    
                merged_list = tuple(zip(resenas, id_producto))  
                return merged_list

            resenas = []
            id_producto = []

            for val in lifestore_sales: 
                resenas.append(val[2])
  
            for id in lifestore_sales: 
                id_producto.append(id[1])

            lista_fusion = merge(id_producto, resenas)

            repeticiones = {}

            for n in lista_fusion:
                if n in repeticiones :
                    repeticiones[n] += 1
                else:
                    repeticiones[n] = 0
   
            primero = (collections.Counter(repeticiones).most_common()[0][0])
            segundo = (collections.Counter(repeticiones).most_common()[1][0])
            tercero = (collections.Counter(repeticiones).most_common()[2][0])
            cuarto = (collections.Counter(repeticiones).most_common()[3][0])
            quinto = (collections.Counter(repeticiones).most_common()[4][0])


            print(lifestore_products[(primero[0])-1][1],'\n',
                lifestore_products[(segundo[0])-1][1],'\n',
                lifestore_products[(tercero[0])-1][1],'\n',
                lifestore_products[(cuarto[0])-1][1],'\n',
                lifestore_products[(quinto[0])-1][1],'\n',
                )
      
        elif seleccion =='2': #Productos con peores
            print(clr_sub+'Productos con peores reseñas'+clr_reset)
            def merge(resenas, id_producto):    
                merged_list = tuple(zip(resenas, id_producto))  
                return merged_list

            resenas = []
            id_producto = []

            for val in lifestore_sales: 
                resenas.append(val[2])
  
            for id in lifestore_sales: 
                id_producto.append(id[1])

            lista_fusion = merge(id_producto, resenas)

            repeticiones = {}

            for n in lista_fusion:
                if n in repeticiones :
                    repeticiones[n] += 1
                else:
                    repeticiones[n] = 0
   
            primero = (collections.Counter(repeticiones).most_common()[-1][0])
            segundo = (collections.Counter(repeticiones).most_common()[-2][0])
            tercero = (collections.Counter(repeticiones).most_common()[-3][0])
            cuarto = (collections.Counter(repeticiones).most_common()[-4][0])
            quinto = (collections.Counter(repeticiones).most_common()[-5][0])


            print('\n',
lifestore_products[(primero[0])-1][1],'\n',
lifestore_products[(segundo[0])-1][1],'\n',
lifestore_products[(tercero[0])-1][1],'\n',
lifestore_products[(cuarto[0])-1][1],'\n',
lifestore_products[(quinto[0])-1][1],'\n',
                )
            
        
        else:
            print('La función', seleccion , 'NO es valida')
          
    elif seleccion == '3': #Ingresos
        print('Opción seleccionada:' +clr_tit+"Ingresos."+clr_reset)
              
        id_fecha =[[sale[0], sale[3]] for sale in lifestore_sales if sale[4]==0]

        meses ={}

        for par in id_fecha:
            id = par[0]
            _,mes,_ = par[1].split('/')
            if mes not in meses.keys():
                meses[mes]=[]
            meses[mes].append(id)

        for key in meses.keys():
            list_mes = meses[key]
            venta =0
            for id_venta in list_mes:
                indice =id_venta-1
                info_venta =lifestore_sales[indice]
                id_prod = info_venta[1]
                precio = lifestore_products[id_prod-1][2]
                venta += precio
                if key =='01':
                    key= 'Enero'
                elif key =='02':
                    key= 'Febrero'
                elif key == '03':
                    key='Marzo'
                elif key == '04':
                    key = 'Abril'
                elif key == '05':
                    key='Mayo'
                elif key == '06':
                    key='Junio'
                elif key == '07':
                    key='Julio'
                elif key == '08':
                    key='Agosto'
                elif key == '09':
                    key='Septiembre'
                elif key == '10':
                    key='Octubre'
                elif key == '11':
                    key='Noviembre'
                elif key == '12':
                    key='Diciembre'
            
            print('Durante el mes de:',clr_mes,negrita,key,clr_reset,'\n Se realizó una venta por:',Fore.RED,negrita,venta,clr_reset,'MXN\n', 'Con un total de:',clr_items, negrita,len(list_mes),clr_reset,'articulos vendidos')
                               
        
    else: #Funcion no valida
        print('La función', seleccion ,  'NO es válida') 

else:   #Mensaje en pantalla al exceder 3 intentos de incio de sesión
  print(backneg + fneg + 'Intentos de acceso excedidos'+clr_reset)  
