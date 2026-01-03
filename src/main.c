#include "raylib.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


typedef enum {
    BLOQUE_VACIO = 0,
    BLOQUE_MONEDA,
    BLOQUE_OBJETO,
    BLOQUE_NORMAL
} TipoBloque;


typedef struct {
    float posX;
    float posY;
    float escala;
    int item_activo;    // 0 = no activo, 1 = cayendo, 2 = en movimiento horizontal, etc.
    float posX_item;
    float posY_item;
    float velocidad_item_X;
    float velocidad_item_Y;
    int recolectado;
    Rectangle rect;
    TipoBloque tipo;    // Tipo de bloque
    bool bloque_roto;   // Para saber si ya fue golpeado y desaparece
} Bloque;

// opciones para menu de juego

typedef enum {
    CONTINUAR_PARTIDA,
    GUARDAR_PARTIDA,
    MENU_PRINCIPAL_PAUSA,
    SALIR_PAUSA,
    NUM_OPCIONES_PAUSA
} OPCIONES_PAUSA;


//-------------------- ESTRUCTURA DE MENÚ PRINICIPAL ---------------------------
typedef enum{
    Iniciar_Partida,
    Cargar_Partida,
    Opciones,
    Salir,
    num_opc
}MENU_PRINCIPAL;


//-------------------- ESTRUCTURA DE MENÚ DEL TUTORIAL -------------------------
typedef enum{
    PREGUNTA,
    SI,
    NO,
    num_opc1
}MENU_DE_TUTORIAL;

typedef enum{
    Continuar_partida,
    Salir_a_menu_principal,
    num_opc2
}MENU_DE_PAUSA;

//--------------------- CONFIGURACION GENERAL ---------------------
float anchoPantalla = 1280.0f;
float altoPantalla = 720.0f;
int estadoJuego = 0;
float volumenJuego = 1.0f;
int tutorial_paso = 0;
int paso_tutorial = 0;
int mensaje_completo_mostrado = 0;
float tiempo_inicio_tutorial = 0.0f;
float tiempo_mostrar_siguiente_tutorial = 0.0f;
int tecla_presionada_tutorial = 0;
float tiempo_tecla_presionada_tutorial = 0.0f;
float tiempo_fin_tutorial = 0.0f;
float fade_out_tutorial = 0.0f;
bool iniciar_fade_out = false;
float desplazamiento_fondo = 0.0f;
int sound = 0;

//-------------------------- EFECTOS VISUALES ---------------------------------------
float pos_textoX = 0.0f;
float pos_textoY = 0.0f;
int tamano_texto = 40;
float espaciado_texto = 5.0f;
int mostrar_texto = 1;
int mostrar_texto_parpadeante = 0;
float tiempo_parpadeante = 0.0f;
float difuminado = 1.0f;
float velocidad_difuminado = 1.0f;
float tiempo_espera = 0.0f;
float tiempo_menu = 0.0f;
float ultimo_tiempo_sonido = 0.0f;
float intervalo_sonido = 0.05f;
int ultimo_caracter_mostrado = 0;
bool tutorial_iniciado = false;
int paso_mensaje_quetzal = 0;
int mensaje_quetzal_mostrado = 0;  // Control para mostrar mensaje completo
float tiempo_inicio_quetzal = 0.0f;
int mensaje_ciudad_mostrado = 0;  // Para controlar máquina de escribir del mensaje "Bienvenido"
float tiempo_inicio_ciudad = 0.0;
bool mostrar_flashback = false;
float fade_flashback = 0.0f;
float tiempo_inicio_flashback = 0.0f;
int mensaje_flashback_mostrado = 0;
float tiempo_inicio_mensaje_flashback = 0.0f;
float margen = 20.0f;  // margen alrededor del cuadro de texto
bool esperar_enter_tenochtitlan = false;
bool quetzal_despidiendose = false;
float tiempo_inicio_despedida = 0.0f;
float fade_despedida = 0.0f;
bool mostrar_fade_in_despedida = false;
bool quetzal_se_va = false;
float velX_quetzal_despedida = -2.0f;  // Velocidad hacia la izquierda
bool hud_mostrar = false;
int opcionPausa = 0;
int tecla_izquierda = KEY_A;
int tecla_derecha = KEY_D;
int tecla_salto = KEY_SPACE;
int tecla_agachar = KEY_LEFT_CONTROL;
int tecla_correr = KEY_LEFT_SHIFT;
int tecla_remapeando = 0; // 0 = ninguna, 1-5 = teclas en proceso
bool esperando_tecla = false;
bool juegoPausado = false;
bool mostrarMensajeTeclaUsada = false;
int tiempoMensajeTeclaUsada = 0;
bool iniciar_juego = false;
bool mostrar_comercio = false;
float tiempo_inicio_comercio = 0.0f;
float tiempo_inicio_mensaje_comercio = 0.0f;
int mensaje_comercio_mostrado = 0;
bool mostrar_segundo_mensaje_comercio = false; // Control para el segundo mensaje
int mensaje_segundo_comercio_mostrado = 0;    // Máquina de escribir para segundo mensaje
float tiempo_inicio_segundo_mensaje_comercio = 0.0f;
int mensaje_tercer_comercio_mostrado = 0;     // Máquina de escribir para el tercer mensaje
float tiempo_inicio_tercer_mensaje_comercio = 0.0f;
int paso_mensaje_comercio = 0;




//-------------------------- TUTORIAL -----------------------------------------------
float tiempo_tutorial = 0.0f; // Tiempo de tutorial
bool control_D = false;
bool control_A = false;
bool control_ESPACIO = false;
bool control_CTRL_IZQ = false;
bool control_SHIFT = false;
bool instruccion_D = false;
bool instruccion_A = false;
bool instruccion_ESPACIO = false;
bool instruccion_CTRL_IZQ = false;
bool instruccion_SHIFT = false;
bool tutorial_completo = false;
bool mostrar_continuar = false;
float tiempo_tecla_presionada = 0.0f;

//-------------------------- JUGADOR -------------------------------------------------
float posX = 0.0f;
float posY = 500.0f;
float velX = 0.0f;
float velY = 0.0f;
float gravedad = 0.5f;
float gravedad_normal = 0.5f;
float gravedad_caida = 0.8f;
float fuerza_salto = -50.0f;
float fuerza_Salto_extra = -15.0f;
float tiempo_salto = 0.0f;
float tiempo_max_salto = 0.2f;
int saltando = 0;
int agachado = 0;
float tamano_normal = 181.0f;
float tamano_agachado = 150.0f;
float escala;
int mirando_derecha = 1;
int frame_caminar = 0;
int estado_caminar = 0;
int vidas = 5;
int puntuacion = 0;
int tiempo = 400;
int monedas = 0;
float acumulador_tiempo = 0.0f;
float velocidad_tiempo = 2.0f;
bool enSuelo = false;
bool enBloque = false;

//------------------ ENEMIGO (POLI ESQUELETO) --------------------------------------
float posX_poli = 1500.0f;
float posY_poli = 520.0f;
float velocidad_poli = 5.0f;
float tamano_poli = 130.0f;
float escala_poli;
int poli_caminando = 0;  // 0: quieto, 1: caminando
int frame_poli = 0;

//------------------ QUETZALCOATL --------------------------------------
float posX_quez = 1300.0f;
float posY_quez = 460.0f;
float velX_quez = 5.0f;          // Velocidad de movimiento
float animSpeed = 0.2f;          // Velocidad de animación (segundos por frame)
float animTimer = 0.0f;          // Temporizador para animación
int currentFrame = 0;            // Frame actual de animación
Texture2D quetzalFrames[2];      // Array para almacenar frames de animación
int frame_camina_quetz = 0;
int estado_camina_quetz = 0;
bool quetzal_llego = false;
bool en_cinematica_quetzal = false;

//------------------ CÁMARA ---------------------------------------------------
Camera2D camara = {0};
float limiteIzquierdo = 0.0f;
float limiteDerecho;

//------------------- MENÚ PRINCIPAL ------------------------------------------
int opc = 0;
int confirmar_opc = 0;
float tiempo_sel = 0.0f;
float tiempo_cambio = 0.0f;
float difuminado_menu = 1.0f;

//------------------- MENÚ DE OPCIONES ----------------------------------------
int enOpciones = 0;
//------------------ BLOQUE E ITEM --------------------------------------
float posX_bloque = 600.0f;
float posY_bloque = 350.0f;
float escala_bloque = 0.025f;
float posX_item = 0.0f;
float posY_item = 0.0f;
float velocidad_item_X = 2.0f;
float velocidad_item_Y = 0.0f;
float gravedad_item = 0.1f;
int item_activo = 0;
float radio_item = 20.0f;
Bloque bloques[100];
int num_bloques = 100;



//-------------------- SONIDO --------------------------------------------------
Sound sonido_salto;
Sound sonido_escribir;
Sound item;
Sound power_up;

//-------------------- MÚSICA --------------------------------------------------
Music musica;
Music level1_music;


//------------------- TEXTURAS ------------------------------------------------
Texture2D textura_jugadorDerecha;
Texture2D textura_jugadorIzquierda;
Texture2D textura_agachadoDerecha;
Texture2D textura_agachadoIzquierda;
Texture2D textura_saltoDerecha;
Texture2D textura_saltoIzquierda;
Texture2D textura_caminarDerecha1;
Texture2D textura_caminarDerecha2;
Texture2D textura_caminarIzquierda1;
Texture2D textura_caminarIzquierda2;
Texture2D textura_vida;
Texture2D textura_actual;
Texture2D fondo1;
Texture2D fondo_bucle;
Texture2D textura_quetzalcoatl_izquierda;
Texture2D textura_quetzalcoatl_derecha;
Texture2D textura_quetzalcoatl_caminado_izquierda;
Texture2D textura_quetzalcoatl_caminado_derecha;
Texture2D textura_muro_huacal;
Texture2D textura_comercio;
Texture2D textura_tenochtitlan;
Texture2D textura_cacao_dorado;
Texture2D titulo;
Image icono;
Texture2D reloj;
Texture2D moneda;
Texture2D bloque;
Rectangle rectMauricio;
Rectangle rectEsqueleto;
Rectangle rectBloque;
Rectangle rectSuelo;
Rectangle rectquez;
Texture2D textura_quetzalcoatl_actual;
Texture2D textura_poli_quieto_derecha;        // Policia quieto mirando derecha
Texture2D textura_poli_quieto_izquierda; // Policia quieto mirando izquierda
Texture2D textura_poli_caminando_derecha;                  // Policia caminando mirando derecha
Texture2D textura_poli_caminando_izquierda;       // Policia caminando mirando izquierda
Texture2D textura_taco_malo_quieto;
Texture2D textura_taco_malo_caminado_derecha;
Texture2D textura_taco_malo_caminado_izquierda;
Texture2D textura_indigena_quieto_derecha;
Texture2D textura_indigena_quieto_izquierda;
Texture2D textura_jugadorFireDerecha;
Texture2D textura_jugadorFireIzquierda;


//--------------------------------- FUNCIONES --------------------------------------------
void Cargar_recursos();
void Descargar_recursos();
void Configuracion_camara();
void Dibujar_presentacion();
void Dibujar_menu_enter();
void Dibujar_menu_principal();
void Dibujar_menu_tutorial();
void Dibujar_tutorial();
void Dibujar_juego();
void Dibujar_menu_pausa();
void Actualizar_fisicas();
void Actualizar_animaciones();
void Actualizar_camara();
void Actualizar_menu_principal();
void Actualizar_menu_tutorial();
void Actualizar_menu_pausa();
void Ejecutar_opcion();
bool CheckCollision(Rectangle, Rectangle);
void InicializarBloques();
bool ActualizarColisiones();
void Actualizar_quetzalcoatl();
void mostrar_mensaje_quez();
void CargarPartida();
void ReiniciarJuego();
void GuardarPartida();
char * GetKeyName(int);
char* nombreTecla(int key);
void actualizarMenuOpciones();
void dibujarMenuOpciones();
bool teclaAsignada(int);







int main(){
    srand(time(NULL));

    InitWindow(anchoPantalla, altoPantalla, "MAURICIO EL SALTA MUROS");
    InitAudioDevice();

    Cargar_recursos();

    Configuracion_camara();

    SetTargetFPS(60);

    SetMusicVolume(musica, 0.1f);


    //----------------------- BUCLE PRINCIPAL DEL JUEGO --------------------------
    while(WindowShouldClose() == false){

        if(IsKeyPressed(KEY_F11) == true)
            ToggleFullscreen();

        tiempo_parpadeante += GetFrameTime();
        if(tiempo_parpadeante >= 0.3f){
            tiempo_parpadeante = 0.0f;
            if(mostrar_texto_parpadeante == 1)
                mostrar_texto_parpadeante = 0;
            else
                mostrar_texto_parpadeante = 1;
        }

         //------------------------ ESTADOS DE JUEGO -----------------------------------------
        switch(estadoJuego){
            case 0:
                //----------- ESTADO 0: PRESENTACIÓN DE MarQUEZ -----------------------------

                // Parar música
                StopMusicStream(musica);

                // Acumula tiempo total en presentación
                tiempo_espera += GetFrameTime();

                // 0–3 s: nada visible aún
                if (tiempo_espera < 3.0f)
                    difuminado = 0.0f;

                // 3–6 s: fade-in (0 -> 1)
                else if (tiempo_espera < 6.0f)
                    difuminado = (tiempo_espera - 3.0f) / 3.0f;

                // 6–9 s: mantener al 100%
                else if (tiempo_espera < 9.0f)
                    difuminado = 1.0f;

                // 9–12 s: fade-out (1 -> 0)
                else if (tiempo_espera < 12.0f) {
                    difuminado = 1.0f - (tiempo_espera - 9.0f) / 3.0f;
                }
                // Luego de 12 s: pasar al menú de ENTER
                else {
                    tiempo_espera  = 0.0f;
                    posX = (anchoPantalla / 2) - 70;
                    difuminado  = 0.0f; // menú inicia opaco
                    estadoJuego  = 1;
                }
                break;

            case 1:
                //----------- ESTADO 1: MENÚ DE ENTER -----------------------------

                // Acumula tiempo total del menú de enter
                tiempo_menu += GetFrameTime();

                // Esperar 2 segundos sin mostrar texto
                if (tiempo_menu < 1.0f)
                    difuminado = 0.0f;  // Aún no empieza el difuminado

                // De 2 a 3 segundos: hacer el fade-in rápido
                else if (tiempo_menu < 3.0f)
                    difuminado = (tiempo_menu - 2.0f) / 1.0f;  // Difuminado de 0 -> 1 en un segundo


                // Reproducir música para el menú ENTER
                 if (IsMusicStreamPlaying(musica) == false)
                        PlayMusicStream(musica);

                // Cambiar de menú
                if(IsKeyPressed(KEY_ENTER) == true){
                    posX = 0.0f;
                    posY = 500.0f;
                    mirando_derecha = 1;
                    textura_actual = textura_jugadorDerecha; // Actualizar textura del jugador mirando a la derecha
                    estadoJuego = 2; // Pasar a Menú principal
                    difuminado = 1.0f;
                }

                // Actualizar física del jugador (para que se mueva en el fondo)
                Actualizar_fisicas();
                Actualizar_animaciones();
                break;

            case 2:
                //----------- ESTADO 2: MENÚ PRINCIPAL ----------------------------

                // Reproducir música para el menú principal
                 if (IsMusicStreamPlaying(musica) == false)
                        PlayMusicStream(musica);

                // Actualizar opciones del menú principal
                Actualizar_menu_principal();
                break;

            case 3:
                //----------- ESTADO 3: MENÚ DE TUTORIAL --------------------------

                // Reproducir música para el menú de tutorial
                if (IsMusicStreamPlaying(musica) == false)
                        PlayMusicStream(musica);

                Actualizar_menu_tutorial();
                break;

            case 4:
                //----------- ESTADO 4: TUTORIAL ----------------------------------

                //Parar música
                StopMusicStream(musica);

                if(mostrar_texto == 1){
                    // Esperar 3s tras mostrar mensaje completo
                    if(mensaje_completo_mostrado == 1 && GetTime() - tiempo_mostrar_siguiente_tutorial >= 3.0f){
                        // Para pasos 0 y 1 avanza solo
                        if(paso_tutorial < 2){
                            mensaje_completo_mostrado = 0;
                            paso_tutorial++;
                            tiempo_inicio_tutorial = GetTime();
                        }
                        else {
                            // Detectar acción correcta sin variables nuevas
                            bool key_ok = false;

                            switch(paso_tutorial) {
                                case 2:
                                    if(IsKeyReleased(KEY_D) == true)
                                        key_ok = true;
                                    break;
                                case 3:
                                    if(IsKeyReleased(KEY_A) == true)
                                        key_ok = true;
                                    break;
                                case 4:
                                    if(IsKeyPressed(KEY_SPACE) == true)
                                        key_ok = true;
                                    break;
                                case 5:
                                    if(IsKeyReleased(KEY_LEFT_CONTROL) == true)
                                        key_ok = true;
                                    break;
                                case 6:
                                    if(IsKeyReleased(KEY_LEFT_SHIFT) == true)
                                        key_ok = true;
                                    break;
                            }
                            if(key_ok == true){
                                // Acción instantánea
                                mensaje_completo_mostrado = 0;
                                paso_tutorial++;
                                tiempo_inicio_tutorial = GetTime();
                                // Reiniciar animación caminata
                                estado_caminar = 0;
                                frame_caminar = 0;
                                // Si fue el último paso, terminar tutorial
                                if (paso_tutorial > 6) {
                                    mostrar_texto = 1;
                                    paso_tutorial = 7;
                                    mensaje_completo_mostrado = 0;
                                    tiempo_inicio_tutorial = GetTime();

                                }
                            }
                        }
                    }
                }

                // Actualizar física y animaciones
                // Mantener salto hasta el suelo
                if(saltando == 1){
                    Actualizar_fisicas();
                    Actualizar_animaciones();
                    if(posY >= 500.0f){
                        saltando = 0;
                        estado_caminar = 0;
                        frame_caminar = 1;
                    }
                }
                else {

                    Actualizar_fisicas();
                    Actualizar_animaciones();
                }
                break;

            case 5:
                //----------- ESTADO 5: INICIO DE JUEGO ----------------------------------
                // Parar música
                PauseMusicStream(musica);


                 if (IsKeyPressed(KEY_P)) {
                    juegoPausado = !juegoPausado;
                    if (juegoPausado) {
                        StopSound(sonido_escribir);
                        PauseMusicStream(level1_music);
                        estadoJuego = 6;  // Cambiar al menú de pausa
                    } else {
                        ResumeSound(sonido_escribir);
                        ResumeMusicStream(level1_music);
                        estadoJuego = 5;  // Volver al juego
                    }
                }

                if(mostrar_texto == 2){
                    // Solo actualizar animaciones mientras se muestra el mensaje
                    Actualizar_animaciones();

                    mirando_derecha = 1;

                    // Controlar el mensaje de inicio
                    if (mensaje_completo_mostrado == 0) {
                        float tiempo_actual = GetTime() - tiempo_inicio_tutorial;
                        if (tiempo_actual >= strlen("Bienvenido a Ciudad de México") / 20.0f) {
                            mensaje_completo_mostrado = 1;
                            tiempo_mostrar_siguiente_tutorial = GetTime();
                        }
                    }

                    PlayMusicStream(level1_music);

                    // Detectar ENTER para continuar
                    if (mensaje_completo_mostrado == 1 && IsKeyPressed(KEY_ENTER) == true) {
                        StopSound(sonido_escribir);
                        mostrar_texto = 0; // Cambiar a juego normal

                        en_cinematica_quetzal = true;

                        ResumeMusicStream(level1_music);

                        quetzal_llego = false;
                        frame_camina_quetz = 0;
                        estado_camina_quetz = 0;


                    }

                }
                else {
                    UpdateMusicStream(level1_music);





                    // Juego normal
                    // Actualizar tiempo (sistema con enteros pero velocidad acelerada)

                    if (en_cinematica_quetzal && posX_quez <= posX + 200.0f) {
                        PauseMusicStream(level1_music);
                    }
                    // Añadir este bloque para reanudar cuando termine la cinemática
                    else if (!en_cinematica_quetzal && !IsMusicStreamPlaying(level1_music)) {
                        ResumeMusicStream(level1_music);
                    }
                    if (estadoJuego == 5 && !en_cinematica_quetzal && !mostrar_flashback) {
                        acumulador_tiempo += GetFrameTime() * velocidad_tiempo;
                        if (acumulador_tiempo >= 1.0f && tiempo > 0) {
                            tiempo -= (int)acumulador_tiempo;
                            acumulador_tiempo -= (int)acumulador_tiempo;
                            if (tiempo <= 0) {
                                tiempo = 0;
                                vidas--;
                                if (vidas <= 0) {
                                    estadoJuego = 2;
                                    vidas = 5;
                                    tiempo = 400;
                                } else {
                                    posX = 0.0f;
                                    posY = 500.0f;
                                    tiempo = 400;
                                }
                            }
                        }
                    }

                        if(!en_cinematica_quetzal && !mostrar_flashback && !mostrar_fade_in_despedida && !quetzal_despidiendose && !quetzal_se_va){
                            Actualizar_fisicas();
                        }
                        Actualizar_animaciones();
                        Actualizar_camara();
                        Actualizar_quetzalcoatl();




                }
                break;
            case 6:
                Actualizar_menu_pausa();
                break;
            case 7:
                actualizarMenuOpciones();
             break;

        }

        //---------------------------- RENDERIZADO -----------------------------------
            BeginDrawing();
                switch(estadoJuego){
                    case 0:
                        Dibujar_presentacion();
                        break;
                    case 1:
                        Dibujar_menu_enter();
                        break;
                    case 2:
                        Dibujar_menu_principal();
                        break;
                    case 3:
                        Dibujar_menu_tutorial();
                        break;
                    case 4:
                        Dibujar_tutorial();
                        break;
                    case 5:
                        Dibujar_juego();
                        break;
                    case 6:
                        Dibujar_menu_pausa();
                        break;
                    case 7:
                        dibujarMenuOpciones();
                        break;
                }
            EndDrawing();
            UpdateMusicStream(musica);


    }

    Descargar_recursos();
    CloseAudioDevice();
    CloseWindow();
    return 0;

}


//--------------------------------- FUNCIONES --------------------------------------------
void Cargar_recursos(){

    textura_jugadorDerecha = LoadTexture("mauricio.png");
    textura_jugadorIzquierda = LoadTexture("mauricio2.png");
    textura_agachadoDerecha = LoadTexture("crouch.png");
    textura_agachadoIzquierda = LoadTexture("crouch2.png");
    textura_saltoDerecha = LoadTexture("jumping.png");
    textura_saltoIzquierda = LoadTexture("jumping2.png");
    textura_caminarDerecha1 = LoadTexture("walkingright1.png");
    textura_caminarDerecha2 = LoadTexture("walkingright2.png");
    textura_caminarIzquierda1 = LoadTexture("walkingleft1.png");
    textura_caminarIzquierda2 = LoadTexture("walkingleft2.png");
    textura_vida = LoadTexture("vida.png");
    textura_actual = textura_jugadorDerecha;
    fondo1 = LoadTexture("reformaday.png");
    fondo_bucle = LoadTexture("bucle.png");
    titulo = LoadTexture("title.png");
    icono = LoadImage("title.png");
    reloj = LoadTexture("clock.png");
    moneda = LoadTexture("coin.png");
    bloque = LoadTexture("block.jpg");
    musica = LoadMusicStream("music.mp3");
    SetWindowIcon(icono);
    sonido_salto = LoadSound("jump.wav");
    sonido_escribir = LoadSound("writing.wav");
    item = LoadSound("item.wav");
    power_up = LoadSound("powerup.wav");
    textura_quetzalcoatl_izquierda = LoadTexture("quetzalcoatl_left.png");
    textura_quetzalcoatl_derecha = LoadTexture("quetzalcoatl_right.png");
    textura_quetzalcoatl_caminado_izquierda = LoadTexture("quetzalcoatl_walking_left.png");
    textura_quetzalcoatl_caminado_derecha = LoadTexture("quetzalcoatl_walking_right.png");
    textura_muro_huacal = LoadTexture("jump_wall_huacal.png");
    textura_comercio =  LoadTexture("commerce_post.png");
    textura_tenochtitlan = LoadTexture("tenochtitlan.png");
    textura_cacao_dorado = LoadTexture("golden_cacao.png");
    level1_music = LoadMusicStream("level1_music.mp3");
    textura_poli_quieto_izquierda = LoadTexture("poli_quieto_izquierda.png");
    textura_poli_quieto_derecha = LoadTexture("poli_quieto_derecha.png");
    textura_poli_caminando_izquierda= LoadTexture("poli_caminando_izquierda.png");
    textura_poli_caminando_derecha = LoadTexture("poli_caminando_derecha.png");
    textura_taco_malo_quieto = LoadTexture("taco_malo_quieto.png");
    textura_taco_malo_caminado_derecha = LoadTexture("taco_malo_caminado_derecha.png");
    textura_taco_malo_caminado_izquierda = LoadTexture("taco_malo_caminado_izquierda.png");
    textura_indigena_quieto_derecha = LoadTexture("indigena_quieto_derecha.png");
    textura_indigena_quieto_izquierda = LoadTexture("indigena_quieto_izquierda.png");
    textura_jugadorFireDerecha = LoadTexture("fire1.png");
    textura_jugadorFireIzquierda = LoadTexture("fire2.png");

    InicializarBloques();
}

void Descargar_recursos(){

UnloadTexture(textura_jugadorDerecha);
UnloadTexture(textura_jugadorIzquierda);
UnloadTexture(textura_agachadoDerecha);
UnloadTexture(textura_agachadoIzquierda);
UnloadTexture(textura_saltoDerecha);
UnloadTexture(textura_saltoIzquierda);
UnloadTexture(textura_caminarDerecha1);
UnloadTexture(textura_caminarDerecha2);
UnloadTexture(textura_caminarIzquierda1);
UnloadTexture(textura_caminarIzquierda2);
UnloadTexture(textura_jugadorFireDerecha);
UnloadTexture(textura_jugadorFireIzquierda);
UnloadTexture(fondo1);
UnloadTexture(fondo_bucle);
UnloadTexture(titulo);
UnloadTexture(reloj);
UnloadTexture(moneda);
UnloadTexture(bloque);
UnloadTexture(textura_vida);
UnloadTexture(textura_muro_huacal);
UnloadTexture(textura_comercio);
UnloadTexture(textura_tenochtitlan);
UnloadTexture(textura_cacao_dorado);
UnloadTexture(textura_quetzalcoatl_izquierda);
UnloadTexture(textura_quetzalcoatl_derecha);
UnloadTexture(textura_quetzalcoatl_caminado_izquierda);
UnloadTexture(textura_quetzalcoatl_caminado_derecha);
UnloadTexture(textura_poli_quieto_izquierda);
UnloadTexture(textura_poli_quieto_derecha);
UnloadTexture(textura_poli_caminando_izquierda);
UnloadTexture(textura_poli_caminando_derecha);
UnloadTexture(textura_taco_malo_quieto);
UnloadTexture(textura_taco_malo_caminado_derecha);
UnloadTexture(textura_taco_malo_caminado_izquierda);
UnloadTexture(textura_indigena_quieto_derecha);
UnloadTexture(textura_indigena_quieto_izquierda);
UnloadImage(icono);
UnloadSound(sonido_salto);
UnloadSound(sonido_escribir);
UnloadSound(item);
UnloadSound(power_up);
UnloadMusicStream(musica);
UnloadMusicStream(level1_music);
}

void Configuracion_camara(){

    camara.target = (Vector2){anchoPantalla / 2, 360.0f};  // Empieza centrada en pantalla
    camara.offset = (Vector2){anchoPantalla / 2, altoPantalla / 2};
    camara.rotation = 0.0f;
    camara.zoom = 1.0f;
}

void Dibujar_presentacion(){

    ClearBackground(BLACK);
    Vector2 texto = MeasureTextEx(GetFontDefault(), "- MarQUEZ presenta -", tamano_texto, espaciado_texto);
    pos_textoX = (anchoPantalla - texto.x) / 2;
    pos_textoY = (altoPantalla - texto.y) / 2;
    DrawTextEx(GetFontDefault(), "- MarQUEZ presenta -", (Vector2){pos_textoX, pos_textoY}, tamano_texto, espaciado_texto, Fade(WHITE, difuminado));
}

void Dibujar_menu_enter(){

    // Dibujar fondo
    DrawTexture(fondo1, 0, 0, Fade(DARKGRAY, difuminado));

    // Dibujar jugador
    if(agachado == 1)
        DrawTextureEx(textura_actual, (Vector2){posX, posY + 10}, 0.0f, escala, Fade(WHITE, difuminado));
    else
        DrawTextureEx(textura_actual, (Vector2){posX, posY}, 0.0f, escala, Fade(WHITE, difuminado));

    // Dibujar texto del menú
    Vector2 texto1 = MeasureTextEx(GetFontDefault(), "Presiona ", tamano_texto-10, espaciado_texto);
    Vector2 texto2 = MeasureTextEx(GetFontDefault(), " ENTER ", tamano_texto-10, espaciado_texto);
    Vector2 texto3 = MeasureTextEx(GetFontDefault(), "para comenzar", tamano_texto-10, espaciado_texto);

    if(IsKeyDown(KEY_F3) == true){
        DrawRectangleLinesEx(rectMauricio, 2, RED);
        DrawRectangleLinesEx(rectSuelo, 2, BLUE);
    }

    float anchoTotal = texto1.x + texto2.x + texto3.x;
    Vector2 posTexto;
    posTexto.x = (anchoPantalla - anchoTotal) / 2;
    posTexto.y = (altoPantalla - texto1.y) / 2 + 100;

    float escalaTitulo = 0.5f;
    Vector2 posTitulo;
    posTitulo.x = (anchoPantalla - titulo.width * escalaTitulo) / 2;

    // Dibujar título
    DrawTextureEx(titulo, posTitulo, 0.0f, escalaTitulo, Fade(WHITE, difuminado));

    // Dibujar texto con sombra
    DrawTextEx(GetFontDefault(), "Presiona", (Vector2){posTexto.x + 2, posTexto.y + 2}, tamano_texto-10, espaciado_texto, Fade(BLACK, difuminado));
    DrawTextEx(GetFontDefault(), "Presiona", posTexto, tamano_texto-10, espaciado_texto, Fade(WHITE, difuminado));

    if (mostrar_texto_parpadeante == 1) {
        DrawTextEx(GetFontDefault(), " ENTER ", (Vector2){posTexto.x + texto1.x + 2, posTexto.y + 2}, tamano_texto-10, espaciado_texto, Fade(BLACK, difuminado));
        DrawTextEx(GetFontDefault(), " ENTER ", (Vector2){posTexto.x + texto1.x, posTexto.y}, tamano_texto-10, espaciado_texto, Fade(YELLOW, difuminado));
    }

    DrawTextEx(GetFontDefault(), "para comenzar", (Vector2){posTexto.x + texto1.x + texto2.x + 2, posTexto.y + 2}, tamano_texto-10, espaciado_texto, Fade(BLACK, difuminado));
    DrawTextEx(GetFontDefault(), "para comenzar", (Vector2){posTexto.x + texto1.x + texto2.x, posTexto.y}, tamano_texto-10, espaciado_texto, Fade(WHITE, difuminado));
}

void Dibujar_menu_principal() {
    ClearBackground(DARKGRAY);

    // Dibujar fondo con cámara
    BeginMode2D(camara);
    DrawTexture(fondo1, 0, 0, Fade(DARKGRAY, difuminado));
    EndMode2D();

    // Título del menú
    char* titulo = "MENU PRINCIPAL";
    int tituloTam = 50;
    Vector2 medidaTitulo = MeasureTextEx(GetFontDefault(), titulo, tituloTam, espaciado_texto);
    DrawTextEx(GetFontDefault(), titulo,
        (Vector2){(anchoPantalla - medidaTitulo.x)/2 + 4, 100 + 4},
        tituloTam, espaciado_texto, Fade(BLACK, difuminado)); // Sombra
    DrawTextEx(GetFontDefault(), titulo,
        (Vector2){(anchoPantalla - medidaTitulo.x)/2, 100},
        tituloTam, espaciado_texto, Fade(WHITE, difuminado)); // Texto principal

    // Opciones del menú
    char opciones[num_opc][20] = {"Iniciar Partida", "Cargar Partida", "Opciones", "Salir"};
    float espacio = 60;
    float posYBase = 250;

    for (int i = 0; i < num_opc; i++) {
        Color colorTexto = (i == opc && mostrar_texto_parpadeante == 1) ? YELLOW : WHITE;

        Vector2 medida = MeasureTextEx(GetFontDefault(), opciones[i], tamano_texto - 10, espaciado_texto);
        float posX = (anchoPantalla - medida.x) / 2;
        float posY = posYBase + i * espacio;

        // Sombra del texto
        DrawTextEx(GetFontDefault(), opciones[i], (Vector2){posX + 2, posY + 2}, tamano_texto - 10, espaciado_texto, Fade(BLACK, difuminado));

        // Texto principal
        DrawTextEx(GetFontDefault(), opciones[i], (Vector2){posX, posY}, tamano_texto - 10, espaciado_texto, Fade(colorTexto, difuminado));

        // Dibujar un marcador (flecha o símbolo) para la opción seleccionada
        if (i == opc) {
            char* flecha = "->";
            DrawTextEx(GetFontDefault(), flecha, (Vector2){posX - 40, posY}, tamano_texto - 10, espaciado_texto, Fade(YELLOW, difuminado));
        }
    }

    const char* pie = "Usa W y S para navegar y ENTER para seleccionar";
    Vector2 medidaPie = MeasureTextEx(GetFontDefault(), pie, 20, 2);
    DrawTextEx(GetFontDefault(), pie,
        (Vector2){(anchoPantalla - medidaPie.x)/2 + 2, altoPantalla - 40 + 2},
        20, 2, Fade(BLACK, difuminado));
    DrawTextEx(GetFontDefault(), pie,
        (Vector2){(anchoPantalla - medidaPie.x)/2, altoPantalla - 40},
        20, 2, Fade(LIGHTGRAY, difuminado));

    DrawText("BACKSPACE: Volver al inicio", 30, 30, 20, YELLOW);
    if(IsKeyPressed(KEY_BACKSPACE))
        estadoJuego = 1;
}




void Dibujar_menu_tutorial(){
    ClearBackground(DARKGRAY);
    DrawTexture(fondo1, 0, 0, Fade(DARKGRAY, difuminado));


    // Tus opciones
    char opciones1[num_opc1][50] = {"¿Deseas ver el tutorial?", "Si", "No"};

    // 1) Primero dibujamos la pregunta fija (índice 0)
    {
        Vector2 m = MeasureTextEx(GetFontDefault(), opciones1[0], tamano_texto-10, espaciado_texto);
        float px = (anchoPantalla - m.x)/2;
        float py = 300;  // posición vertical fija para la pregunta
        // Sombra
        DrawTextEx(GetFontDefault(), opciones1[0], (Vector2){px+2, py+2}, tamano_texto-10, espaciado_texto, Fade(BLACK,1.0f));
        // Texto (siempre blanco, sin parpadeo)
        DrawTextEx(GetFontDefault(), opciones1[0], (Vector2){px, py}, tamano_texto-10, espaciado_texto, Fade(WHITE,1.0f));
    }

    // 2) Ahora “Si” y “No” en misma línea
    {
        // Medidas individuales
        Vector2 mSi = MeasureTextEx(GetFontDefault(), opciones1[1], tamano_texto-10, espaciado_texto);
        Vector2 mNo = MeasureTextEx(GetFontDefault(), opciones1[2], tamano_texto-10, espaciado_texto);

        float espacio = 80;                                     // separación entre “Si” y “No”
        float totalW = mSi.x + espacio + mNo.x;
        float startX = (anchoPantalla - totalW)/2;                     // punto de inicio
        float yOpts = 300 + 80;                                // abajo de la pregunta

        // Dibujar “Si” (índice 1)
        {
            Color col;
            if (opc == 1 && mostrar_texto_parpadeante == 1)
                col = YELLOW;
            else
                col = WHITE;

            float x = startX;
            DrawTextEx(GetFontDefault(), opciones1[1], (Vector2){x+2, yOpts+2}, tamano_texto-10, espaciado_texto, Fade(BLACK,1.0f));
            DrawTextEx(GetFontDefault(), opciones1[1], (Vector2){x, yOpts}, tamano_texto-10, espaciado_texto, Fade(col,1.0f));
        }

        // Dibujar “No” (índice 2)
        {
            Color col;
            if (opc == 2 && mostrar_texto_parpadeante == 1)
                col = YELLOW;
            else
                col = WHITE;

            float x = startX + mSi.x + espacio;
            DrawTextEx(GetFontDefault(), opciones1[2], (Vector2){x+2, yOpts+2}, tamano_texto-10, espaciado_texto, Fade(BLACK,1.0f));
            DrawTextEx(GetFontDefault(), opciones1[2], (Vector2){x, yOpts}, tamano_texto-10, espaciado_texto, Fade(col,1.0f));
        }
    }

    DrawText("BACKSPACE: Volver al menú", 30, 30, 20, YELLOW);
    if(IsKeyPressed(KEY_BACKSPACE))
        estadoJuego = 2;

     const char* pie = "Usa A y D para navegar y ENTER para seleccionar";
    Vector2 medidaPie = MeasureTextEx(GetFontDefault(), pie, 20, 2);
    DrawTextEx(GetFontDefault(), pie,
        (Vector2){(anchoPantalla - medidaPie.x)/2 + 2, altoPantalla - 40 + 2},
        20, 2, Fade(BLACK, difuminado));
    DrawTextEx(GetFontDefault(), pie,
        (Vector2){(anchoPantalla - medidaPie.x)/2, altoPantalla - 40},
        20, 2, Fade(LIGHTGRAY, difuminado));


}

void Dibujar_tutorial(){
    // Si estamos en fade out, dibujamos todo negro
    if (iniciar_fade_out) {
        ClearBackground(Fade(BLACK, fade_out_tutorial));

        // Incrementar el fade out
        fade_out_tutorial += GetFrameTime() * 0.8f; // Ajusta la velocidad del fade

        // Cuando el fade esté completo, cambiar al estado de juego
        if (fade_out_tutorial >= 1.0f) {
            estadoJuego = 5;
            mostrar_texto = 2; // Para mostrar el mensaje de bienvenida
            mensaje_completo_mostrado = 0;
            tiempo_inicio_tutorial = GetTime();
            posX = 0.0f; // Resetear posición del jugador
            posY = 500.0f;
        }
        return; // Salir de la función para no dibujar el resto
    }

    ClearBackground(RAYWHITE);

    // Dibujar fondo y jugador
    if (mostrar_texto == 1) {
        DrawTexture(fondo1, 0, 0, DARKGRAY);
    } else {
        DrawTexture(fondo1, 0, 0, WHITE);
    }

    float dibujarY = posY;
    if (agachado == 1) {
        if (posY >= 500.0f - 1.0f) {
            dibujarY = 500.0f + (tamano_normal - tamano_agachado) + 10;
        }
    } else {
        dibujarY = posY;
    }

    DrawTextureEx(textura_actual, (Vector2){posX, dibujarY}, 0.0f, escala, WHITE);

    if (mostrar_texto == 1) {
        char mensaje_completo[100] = "";
        char mensaje_actual[100] = "";

        // Seleccionar el mensaje según el paso del tutorial
        switch (paso_tutorial) {
            case 0:
                strcpy(mensaje_completo, "Bienvenido al tutorial del juego");
                break;
            case 1:
                strcpy(mensaje_completo, "Los controles para jugar son los siguientes");
                break;
            case 2:
                strcpy(mensaje_completo, "Presiona D para avanzar");
                break;
            case 3:
                strcpy(mensaje_completo, "Presiona A para retroceder");
                break;
            case 4:
                strcpy(mensaje_completo, "Presiona ESPACIO para saltar");
                break;
            case 5:
                strcpy(mensaje_completo, "Presiona CTRL IZQ para agacharte");
                break;
            case 6:
                strcpy(mensaje_completo, "Presiona SHIFT para correr");
                break;
            case 7:
                strcpy(mensaje_completo, "Tutorial completado!");
                // Cuando se muestra "Tutorial completado!", iniciar el temporizador
                if (tiempo_fin_tutorial == 0.0f) {
                    tiempo_fin_tutorial = GetTime();
                }
                // Después de 3 segundos, iniciar el fade out
                else if (GetTime() - tiempo_fin_tutorial >= 3.0f && !iniciar_fade_out) {
                    iniciar_fade_out = true;
                    fade_out_tutorial = 0.0f;
                }
                break;
        }

        // Máquina de escribir
        if (mensaje_completo_mostrado == 0) {
            float tiempo_actual = GetTime() - tiempo_inicio_tutorial;
            int longitud_deseada = (int)(tiempo_actual * 20.0f); // 10 caracteres por segundo

            if (longitud_deseada > strlen(mensaje_completo)) {
                longitud_deseada = strlen(mensaje_completo);
                mensaje_completo_mostrado = 1;
                tiempo_mostrar_siguiente_tutorial = GetTime();
                StopSound(sonido_escribir);
            }
            else{
                if (!IsSoundPlaying(sonido_escribir)) {
                    PlaySound(sonido_escribir);  // 🔈 Iniciamos sonido al escribir
                }
            }


            // Reproducir sonido para cada nuevo carácter
            if (longitud_deseada > ultimo_caracter_mostrado) {
            float tiempo_actual_sonido = GetTime();
            if (tiempo_actual_sonido - ultimo_tiempo_sonido >= intervalo_sonido) {
                sound = 1;
                ultimo_tiempo_sonido = tiempo_actual_sonido;
            }
                ultimo_caracter_mostrado = longitud_deseada;
            }

            strncpy(mensaje_actual, mensaje_completo, longitud_deseada);
            mensaje_actual[longitud_deseada] = '\0';

        } else {
            strcpy(mensaje_actual, mensaje_completo);
        }

        // Configuración de márgenes
        float margen_exterior = 30.0f;
        float margen_interior = 15.0f;
        float max_ancho = anchoPantalla * 0.4f;

        // Medir texto completo
        Vector2 dim_texto = MeasureTextEx(GetFontDefault(), mensaje_completo, tamano_texto-20, espaciado_texto);

        // Calcular ancho del cuadro
        float cuadro_ancho = dim_texto.x + margen_interior * 2;
        if (cuadro_ancho > max_ancho) {
            cuadro_ancho = max_ancho;
        }

        // Posición del cuadro (esquina superior derecha)
        float cuadro_posX = anchoPantalla - cuadro_ancho - margen_exterior;
        float cuadro_posY = margen_exterior;

        // Dividir el texto en palabras
        char palabras[20][50];
        int num_palabras = 0;
        char copia_mensaje[100];
        strcpy(copia_mensaje, mensaje_actual);

        // Separar palabras
        char* token = strtok(copia_mensaje, " ");
        while (token != NULL && num_palabras < 20) {
            strcpy(palabras[num_palabras], token);
            num_palabras++;
            token = strtok(NULL, " ");
        }

        // Calcular líneas necesarias
        float ancho_linea = 0.0f;
        int num_lineas = 1;
        float espacio_entre_lineas = (float)GetFontDefault().baseSize * 2.5f;
        float espacio_extra_entre_palabras = 5.0f;

        // Pre-calcular el alto del cuadro
        for (int i = 0; i < num_palabras; i++) {
            Vector2 medida_palabra = MeasureTextEx(GetFontDefault(), palabras[i], tamano_texto-20, espaciado_texto);
            float espacio = 0.0f;

            if (i < num_palabras-1) {
                espacio = MeasureTextEx(GetFontDefault(), " ", tamano_texto, espaciado_texto).x + espacio_extra_entre_palabras;
            }

            if (i > 0 && (ancho_linea + espacio + medida_palabra.x > (cuadro_ancho - margen_interior * 2))) {
                num_lineas++;
                ancho_linea = 0.0f;
            }
            ancho_linea += medida_palabra.x + espacio;
        }

        // Calcular alto del cuadro
        float cuadro_alto = (num_lineas * espacio_entre_lineas) + margen_interior * 2;

        // Dibujar cuadro de fondo (limpia el área previa)
        DrawRectangle(cuadro_posX, cuadro_posY, cuadro_ancho, cuadro_alto, BLACK);
        DrawRectangleLines(cuadro_posX, cuadro_posY, cuadro_ancho, cuadro_alto, WHITE);

        // Dibujar texto con saltos de línea
        float posX_texto = cuadro_posX + margen_interior;
        float posY_texto = cuadro_posY + margen_interior;
        ancho_linea = 0.0f;

        for (int i = 0; i < num_palabras; i++) {
            Vector2 medida_palabra = MeasureTextEx(GetFontDefault(), palabras[i], tamano_texto-20, espaciado_texto);
            float espacio = 0.0f;

            if (i < num_palabras-1) {
                espacio = MeasureTextEx(GetFontDefault(), " ", tamano_texto, espaciado_texto).x + espacio_extra_entre_palabras;
            }

            // Manejar salto de línea
            if (i > 0 && (ancho_linea + espacio + medida_palabra.x > (cuadro_ancho - margen_interior * 2))) {
                posY_texto += espacio_entre_lineas;
                posX_texto = cuadro_posX + margen_interior;
                ancho_linea = 0.0f;
                // Recalcular espacio para la nueva línea
                if (i < num_palabras-1) {
                    espacio = MeasureTextEx(GetFontDefault(), " ", tamano_texto, espaciado_texto).x + espacio_extra_entre_palabras;
                } else {
                    espacio = 0.0f;
                }
            }

            // Dibujar palabra
            DrawTextEx(GetFontDefault(), palabras[i], (Vector2){posX_texto, posY_texto}, tamano_texto-20, espaciado_texto, WHITE);
            posX_texto += medida_palabra.x + espacio;
            ancho_linea += medida_palabra.x + espacio;
        }
    }
}

void Dibujar_juego(){
    ClearBackground(RAYWHITE);

    // Dibujar fondo
    BeginMode2D(camara);

       // Calcular desplazamiento basado en la posición de la cámara
        desplazamiento_fondo = fmod(camara.target.x * 0.5f, fondo_bucle.width);

        // Calcular cuántas copias del fondo necesitamos dibujar
        int num_copias = 20;
        float posicion_inicial = -desplazamiento_fondo;

        // Dibujar múltiples copias del fondo para cubrir toda el área visible
        if(mostrar_texto == 2 || (posX_quez <= posX + 200.0f) && en_cinematica_quetzal || mostrar_fade_in_despedida || quetzal_despidiendose || quetzal_se_va){
            for (int i = 0; i < num_copias; i++) {
                DrawTexture(fondo_bucle, posicion_inicial + i * fondo_bucle.width, 0, DARKGRAY);
            }
        }
        else{
            for (int i = 0; i < num_copias; i++) {
                DrawTexture(fondo_bucle, posicion_inicial + i * fondo_bucle.width, 0, WHITE);
            }

        }

        if (estadoJuego == 5) {

            DrawTextureEx(textura_quetzalcoatl_actual, (Vector2){posX_quez, posY_quez}, 0.0f, 0.15f, WHITE);
        }


        // Dibujar jugador
        if(agachado == 1)
            DrawTextureEx(textura_actual, (Vector2){posX, posY - 20}, 0.0f, escala, WHITE);
        else
            DrawTextureEx(textura_actual, (Vector2){posX, posY - 30}, 0.0f, escala, WHITE);




        // Dibujar esqueleto
        if (posX_poli >= 0) {
            Texture2D textura_poli_actual;

            if (poli_caminando == 0)
                textura_poli_actual = textura_poli_quieto_izquierda;
            else
                textura_poli_actual = textura_poli_caminando_izquierda;

            DrawTextureEx(textura_poli_actual, (Vector2){posX_poli, posY_poli}, 0.0f, escala_poli, WHITE);
        }


            // Dibujar todos los bloques
            if (mostrar_texto == 0) {
                for (int i = 0; i < num_bloques; i++) {
                    // No dibujar bloques normales/vacíos rotos (desaparecidos)
                    if ((bloques[i].tipo == BLOQUE_VACIO || bloques[i].tipo == BLOQUE_NORMAL) && bloques[i].bloque_roto)
                        continue;

                    Color colorBloque;

                    // Cambiar a gris si el bloque tiene item activo o ya fue recolectado
                    // Determinar el color de los bloques:
                    if (mostrar_texto != 0 || (posX_quez <= posX + 200.0f) && en_cinematica_quetzal || mostrar_fade_in_despedida || quetzal_despidiendose || quetzal_se_va) {
                        // Si hay cinemática o texto, los bloques deben ser de color DARKGRAY
                        colorBloque = DARKGRAY;
                    } else if (bloques[i].item_activo > 0 || bloques[i].recolectado) {
                        // Si el bloque tiene un ítem activo o ya ha sido recolectado, se dibuja en GRAY
                        colorBloque = GRAY;
                    } else {
                        // Si no está golpeado ni tiene ítem, se dibuja en WHITE
                        colorBloque = WHITE;
                    }

                    DrawTextureEx(bloque, (Vector2){bloques[i].posX, bloques[i].posY}, 0.0f, bloques[i].escala, colorBloque);

                    // Dibujar ítem si está activo
                    if (bloques[i].item_activo > 0) {
                        DrawCircle(bloques[i].posX_item, bloques[i].posY_item, radio_item, BLACK);
                    }
                }
            }

            if (IsKeyDown(KEY_F3)) {

            rectMauricio = (Rectangle){posX + 25, posY - 20, textura_actual.width * escala - 50, textura_actual.height * escala - 15};

            // Verifica que los rectángulos de los objetos sean visibles y estén bien definidos
            DrawRectangleLinesEx(rectMauricio, 2, RED);  // Dibuja el contorno de rectMauricio en rojo
            for (int i = 0; i < num_bloques; i++) {
                // Si el bloque no está roto, dibuja su contorno
                if ((bloques[i].tipo == BLOQUE_VACIO || bloques[i].tipo == BLOQUE_NORMAL) && bloques[i].bloque_roto)
                    continue;

                // Actualiza el rectángulo del bloque
                rectBloque = (Rectangle) { bloques[i].posX, bloques[i].posY, bloque.width * bloques[i].escala, bloque.height * bloques[i].escala };

                // Dibuja el contorno del bloque
                DrawRectangleLinesEx(rectBloque, 2, BLUE);  // Dibuja el contorno de rectBloque en azul
            }
            Rectangle rectPoli = {posX_poli + 25 , posY_poli, textura_poli_quieto_izquierda.width * escala_poli - 50 , textura_poli_quieto_izquierda.height * escala_poli};
            DrawRectangleLinesEx(rectPoli, 2, GREEN);

            rectSuelo = (Rectangle){0.0f, 645.0f, 100000.0f, 20.0f};
            DrawRectangleLinesEx(rectSuelo, 2, PURPLE);


        }



    EndMode2D();

    if (hud_mostrar) {
        DrawTextureEx(textura_vida, (Vector2){10, 20}, 0.0f, 0.05f, WHITE);
        DrawText(TextFormat("x%02d", vidas), 55, 40, 30, BLACK);
        DrawText(TextFormat("%08d", puntuacion), 940, 40, 30, BLACK);
        DrawText(TextFormat("%03d", tiempo), 1170, 40, 30, BLACK);
        DrawTextureEx(reloj, (Vector2){1130, 32}, 0.0f, 0.04f, WHITE);
        DrawText(TextFormat("x%02d", monedas), 190, 40, 30, BLACK);
        DrawTextureEx(moneda, (Vector2){150, 30}, 0.0f, 0.04f, WHITE);
    }

    // Despedida: si ENTER es presionado
    if (quetzal_despidiendose && mensaje_quetzal_mostrado == 1 && IsKeyPressed(KEY_ENTER)) {
        quetzal_se_va = true;
    }

    // Movimiento Quetzalcóatl caminando (con animación) y cuando sale de pantalla
    if (quetzal_se_va) {
        Actualizar_quetzalcoatl();
    }
    if (posX_quez <= posX + 200.0f && en_cinematica_quetzal) {
        char mensaje_completo[200] = "";

        // Selección del mensaje según paso_mensaje_quetzal
        switch (paso_mensaje_quetzal) {
            case 0:
                strcpy(mensaje_completo, "Hola, soy Quetzalcóatl, soy el dios de la\ncultura mesoamericana, especialmente azteca.");
                break;
            case 1:
                strcpy(mensaje_completo, "Seré tu guia en todo este viaje por México.");
                break;
            case 2:
                strcpy(mensaje_completo, "Recoge todos los tesoros que encuentres.");
                break;
            case 3:
                strcpy(mensaje_completo, "Evita los enemigos y avanza sin miedo.");
                break;
            default:
                en_cinematica_quetzal = false;  // Finalizar cinemática
                return;  // Salir del bloque si ya terminó
        }

        // Mostrar mensaje con efecto máquina de escribir
        char mensaje_actual[200] = "";

        if (mensaje_quetzal_mostrado == 0) {
            if (tiempo_inicio_quetzal == 0.0) {
                tiempo_inicio_quetzal = GetTime();  // Iniciar tiempo solo al comenzar nuevo mensaje
            }

            float tiempo_actual = GetTime() - tiempo_inicio_quetzal;
            int longitud_deseada = (int)(tiempo_actual * 20.0f);  // Velocidad máquina de escribir
            if (longitud_deseada > strlen(mensaje_completo)) {
                longitud_deseada = strlen(mensaje_completo);
                mensaje_quetzal_mostrado = 1;  // Marcar que el mensaje está completo
                StopSound(sonido_escribir);
            }
            else {
                if (!IsSoundPlaying(sonido_escribir)) {
                    PlaySound(sonido_escribir);  // Iniciamos sonido al escribir
                }
            }


            strncpy(mensaje_actual, mensaje_completo, longitud_deseada);
            mensaje_actual[longitud_deseada] = '\0';
        } else {
            strcpy(mensaje_actual, mensaje_completo);  // Mostrar mensaje completo
            StopSound(sonido_escribir);
        }

        // Dibujar cuadro de texto
        float margen = 30.0f;
        Vector2 dim_texto = MeasureTextEx(GetFontDefault(), mensaje_completo, tamano_texto - 20, espaciado_texto);
        float cuadro_ancho = dim_texto.x + 30;
        float cuadro_alto = dim_texto.y + 20;
        float cuadro_posX = 100.0f;
        float cuadro_posY = 350.0f;

        DrawRectangle(cuadro_posX, cuadro_posY, cuadro_ancho, cuadro_alto, BLACK);
        DrawRectangleLines(cuadro_posX, cuadro_posY, cuadro_ancho, cuadro_alto, WHITE);
        DrawTextEx(GetFontDefault(), mensaje_actual, (Vector2){cuadro_posX + 15, cuadro_posY + 10}, tamano_texto - 20, espaciado_texto, WHITE);

        // Mostrar "Presiona ENTER" cuando el mensaje esté completo
        if (mensaje_quetzal_mostrado == 1) {
            char texto_enter[] = "Presiona ENTER";
            Vector2 medida_enter = MeasureTextEx(GetFontDefault(), texto_enter, tamano_texto - 20, espaciado_texto);
            float posX_enter = cuadro_posX + cuadro_ancho - medida_enter.x - 15;
            float posY_enter = cuadro_posY + cuadro_alto - medida_enter.y - 10;

            if (mostrar_texto_parpadeante == 1) {
                DrawTextEx(GetFontDefault(), texto_enter, (Vector2){posX_enter - 15, posY_enter + 50}, tamano_texto - 20, espaciado_texto, YELLOW);
            }

            if (IsKeyPressed(KEY_ENTER)) {
                paso_mensaje_quetzal++;            // Avanzar al siguiente mensaje
                mensaje_quetzal_mostrado = 0;      // Reiniciar máquina de escribir
                tiempo_inicio_quetzal = 0.0;       // Reiniciar tiempo para nuevo mensaje

                if (paso_mensaje_quetzal > 3) {
                    en_cinematica_quetzal = false;  // Finalizar cinemática
                    // Activar el flashback después de la cinemática
                    mostrar_flashback = true;
                    tiempo_inicio_flashback = GetTime();
                    mensaje_flashback_mostrado = 0;
                    tiempo_inicio_mensaje_flashback = 0.0f;
                    // Pausar la música durante el flashback
                    PauseMusicStream(level1_music);
                }


            }
        }
    }

   if (mostrar_flashback) {
    float tiempo_actual_flashback = GetTime() - tiempo_inicio_flashback;

    if (tiempo_actual_flashback < 1.0f) {
        fade_flashback = tiempo_actual_flashback / 1.0f;
        DrawRectangle(0, 0, anchoPantalla, altoPantalla, Fade(BLACK, fade_flashback));
    } else {
        // Mostrar Tenochtitlan y texto
        DrawTexturePro(textura_tenochtitlan,
            (Rectangle){ 0, 0, (float)textura_tenochtitlan.width, (float)textura_tenochtitlan.height },
            (Rectangle){ 0, 0, anchoPantalla, altoPantalla },
            (Vector2){ 0, 0 }, 0.0f, WHITE);

        char* mensaje_flashback = "La Gran Tenochtitlan, capital del Imperio Azteca,\nfundada en 1325 en un islote del lago de Texcoco.\nCentro de poder, comercio y cultura mesoamericana.";
        char mensaje_parcial[256] = {0};
        if (mensaje_flashback_mostrado == 0) {
            if (tiempo_inicio_mensaje_flashback == 0.0f)
                tiempo_inicio_mensaje_flashback = GetTime();

            float tiempo_mensaje = GetTime() - tiempo_inicio_mensaje_flashback;
            int chars_to_show = (int)(tiempo_mensaje * 20.0f);

            if (chars_to_show > strlen(mensaje_flashback)) {
                chars_to_show = strlen(mensaje_flashback);
                mensaje_flashback_mostrado = 1;
                StopSound(sonido_escribir);
            }
            else {
                if (!IsSoundPlaying(sonido_escribir)) {
                    PlaySound(sonido_escribir);  // Iniciar
                }
            }
            strncpy(mensaje_parcial, mensaje_flashback, chars_to_show);


            float margen = 20.0f;
            Vector2 text_size = MeasureTextEx(GetFontDefault(), mensaje_flashback, tamano_texto-10, espaciado_texto);
            Rectangle text_box = {(anchoPantalla - text_size.x - margen*2)/2, 50, text_size.x + margen*2, text_size.y + margen*2};
            DrawRectangleRec(text_box, Fade(BLACK, 0.7f));
            DrawTextEx(GetFontDefault(), mensaje_parcial, (Vector2){text_box.x + margen, text_box.y + margen}, tamano_texto-10, espaciado_texto, WHITE);
        } else {

            float margen = 20.0f;
            Vector2 text_size = MeasureTextEx(GetFontDefault(), mensaje_flashback, tamano_texto-10, espaciado_texto);
            Rectangle text_box = {(anchoPantalla - text_size.x - margen*2)/2, 50, text_size.x + margen*2, text_size.y + margen*2};
            DrawRectangleRec(text_box, Fade(BLACK, 0.7f));
            DrawTextEx(GetFontDefault(), mensaje_flashback, (Vector2){text_box.x + margen, text_box.y + margen}, tamano_texto-10, espaciado_texto, WHITE);

            if (mostrar_texto_parpadeante == 1) {
                DrawTextEx(GetFontDefault(), "Presiona ENTER", (Vector2){800.0f, 200.0f}, tamano_texto-10, espaciado_texto, YELLOW);
            }

            if (IsKeyPressed(KEY_ENTER)) {
                mostrar_flashback = false;
                mostrar_comercio = true;

            }
        }
    }
}


if (mostrar_comercio) {
    float tiempo_actual_comercio = GetTime() - tiempo_inicio_comercio;

    // FADE IN (solo en primer mensaje)
    if (tiempo_actual_comercio < 1.0f && paso_mensaje_comercio == 0) {
        float alpha = tiempo_actual_comercio / 1.0f;
        DrawRectangle(0, 0, anchoPantalla, altoPantalla, Fade(BLACK, alpha));
    } else {
        // DIBUJAR FONDO
        DrawTexturePro(textura_comercio,
            (Rectangle){ 0, 0, (float)textura_comercio.width, (float)textura_comercio.height },
            (Rectangle){ 0, 0, anchoPantalla, altoPantalla },
            (Vector2){ 0, 0 }, 0.0f, WHITE);

        // Definir los tres mensajes
        char* mensajes_comercio[] = {
            "El comercio en Tenochtitlan se realizaba en grandes mercados\ncomo Tlatelolco, donde se intercambiaban productos de toda\nMesoamérica. Tras la conquista, estos espacios dieron origen\nal comercio colonial que evolucionó hasta formar la gran\nCiudad de México que conocemos hoy.",
            "Los pochtecas no solo comerciaban, también espiaban para\nel emperador azteca (Huey Tlatoani). Iban disfrazados de\nmercaderes, recogían información sobre pueblos rebeldes\no futuras conquistas, ten cuidado con ellos.",
            "Quetzalcóatl tiene una misión para ti,\npor favor pon mucha atención"
        };

        // Variables para el mensaje actual, segun paso
        char* texto_actual = mensajes_comercio[paso_mensaje_comercio];
        int* mensaje_mostrado = NULL;
        float* tiempo_inicio_mensaje = NULL;

        // Asociar punteros según paso
        switch (paso_mensaje_comercio) {
            case 0:
                mensaje_mostrado = &mensaje_comercio_mostrado;
                tiempo_inicio_mensaje = &tiempo_inicio_mensaje_comercio;
                break;
            case 1:
                mensaje_mostrado = &mensaje_segundo_comercio_mostrado;
                tiempo_inicio_mensaje = &tiempo_inicio_segundo_mensaje_comercio;
                break;
            case 2:
                mensaje_mostrado = &mensaje_tercer_comercio_mostrado;
                tiempo_inicio_mensaje = &tiempo_inicio_tercer_mensaje_comercio;
                break;
        }

        char mensaje_parcial[512] = {0};

        // Máquina de escribir
        if (*mensaje_mostrado == 0) {
            if (*tiempo_inicio_mensaje == 0.0f)
                *tiempo_inicio_mensaje = GetTime();

            float tiempo_mensaje = GetTime() - *tiempo_inicio_mensaje;
            int chars_to_show = (int)(tiempo_mensaje * 20.0f);

            if (chars_to_show > strlen(texto_actual)) {
                chars_to_show = strlen(texto_actual);
                *mensaje_mostrado = 1;
                StopSound(sonido_escribir);
            } else {
                if (!IsSoundPlaying(sonido_escribir)) {
                    PlaySound(sonido_escribir);
                }
            }

            strncpy(mensaje_parcial, texto_actual, chars_to_show);
            mensaje_parcial[chars_to_show] = '\0';

            float margen = 20.0f;
            Vector2 text_size = MeasureTextEx(GetFontDefault(), texto_actual, tamano_texto - 10, espaciado_texto);
            Rectangle text_box = { (anchoPantalla - text_size.x - margen * 2) / 2, 50, text_size.x + margen * 2, text_size.y + margen * 2 };
            DrawRectangleRec(text_box, Fade(BLACK, 0.7f));
            DrawTextEx(GetFontDefault(), mensaje_parcial, (Vector2){ text_box.x + margen, text_box.y + margen }, tamano_texto - 10, espaciado_texto, WHITE);
        } else {
            float margen = 20.0f;
            Vector2 text_size = MeasureTextEx(GetFontDefault(), texto_actual, tamano_texto - 10, espaciado_texto);
            Rectangle text_box = { (anchoPantalla - text_size.x - margen * 2) / 2, 50, text_size.x + margen * 2, text_size.y + margen * 2 };
            DrawRectangleRec(text_box, Fade(BLACK, 0.7f));
            DrawTextEx(GetFontDefault(), texto_actual, (Vector2){ text_box.x + margen, text_box.y + margen }, tamano_texto - 10, espaciado_texto, WHITE);

            if (mostrar_texto_parpadeante == 1) {
                DrawTextEx(GetFontDefault(), "Presiona ENTER", (Vector2){ 800.0f, 200.0f }, tamano_texto - 10, espaciado_texto, YELLOW);
            }
        }

        // Detectar ENTER para avanzar mensaje o salir
        if (IsKeyPressed(KEY_ENTER) && *mensaje_mostrado) {
            if (paso_mensaje_comercio < 2) {
                paso_mensaje_comercio++;
            } else {
                // Finalizar comercio y continuar el juego
                mostrar_comercio = false;
                mostrar_fade_in_despedida = true;
                tiempo_inicio_mensaje_comercio = 0.0f;
                fade_despedida = 0.0f;
                tiempo_inicio_despedida = GetTime();

                // Resetear variables de mensajes para la próxima vez
                mensaje_comercio_mostrado = 0;
                mensaje_segundo_comercio_mostrado = 0;
                mensaje_tercer_comercio_mostrado = 0;
                tiempo_inicio_mensaje_comercio = 0.0f;
                tiempo_inicio_segundo_mensaje_comercio = 0.0f;
                tiempo_inicio_tercer_mensaje_comercio = 0.0f;
                paso_mensaje_comercio = 0;
            }
        }
    }
}




// Fade in para regreso al escenario con Quetzalcóatl despidiéndose
if (mostrar_fade_in_despedida) {
    fade_despedida += GetFrameTime();
    DrawRectangle(0, 0, anchoPantalla, altoPantalla, Fade(BLACK, fade_despedida));

    if (fade_despedida >= 1.0f) {
        mostrar_fade_in_despedida = false;
        quetzal_despidiendose = true;
        mensaje_quetzal_mostrado = 0;
        tiempo_inicio_quetzal = GetTime();
        paso_mensaje_quetzal = 0;
        posX_quez = posX + 200.0f;  // Aparece cerca de Mauricio
    }
}

//  Despedida de Quetzalcóatl
if (quetzal_despidiendose) {
    // Dibujar Quetzalcóatl cerca del jugador
    DrawTextureEx(textura_quetzalcoatl_actual, (Vector2){posX_quez, posY_quez}, 0.0f, 0.15f, WHITE);

    char* mensaje_despedida = "Recuerda llevar el cacao dorado\nhasta el final, nos vemos!";
    char mensaje_actual[200] = "";

    if (mensaje_quetzal_mostrado == 0) {
        float tiempo_actual = GetTime() - tiempo_inicio_quetzal;
        int longitud_deseada = (int)(tiempo_actual * 15.0f);
        if (longitud_deseada > strlen(mensaje_despedida)) {
            longitud_deseada = strlen(mensaje_despedida);
            mensaje_quetzal_mostrado = 1;
            StopSound(sonido_escribir);
        }
        else {
                if (!IsSoundPlaying(sonido_escribir)) {
                    PlaySound(sonido_escribir);  // Iniciar
                }
            }
        strncpy(mensaje_actual, mensaje_despedida, longitud_deseada);
        mensaje_actual[longitud_deseada] = '\0';
    } else {
        strcpy(mensaje_actual, mensaje_despedida);
    }

    // Dibujar cuadro de texto
        float margen = 30.0f;
        Vector2 dim_texto = MeasureTextEx(GetFontDefault(), mensaje_actual, tamano_texto - 20, espaciado_texto);
        float cuadro_ancho = dim_texto.x + 30;
        float cuadro_alto = dim_texto.y + 20;
        float cuadro_posX = 100.0f;
        float cuadro_posY = 350.0f;

    // Dibujar mensaje
        DrawRectangle(cuadro_posX, cuadro_posY, cuadro_ancho, cuadro_alto, BLACK);
        DrawRectangleLines(cuadro_posX, cuadro_posY, cuadro_ancho, cuadro_alto, WHITE);
        DrawTextEx(GetFontDefault(), mensaje_actual, (Vector2){cuadro_posX + 15, cuadro_posY + 10}, tamano_texto - 20, espaciado_texto, WHITE);

    if (mensaje_quetzal_mostrado == 1) {
        if (mostrar_texto_parpadeante == 1) {
            // Cambiamos la posición a más abajo y centrado
            const char* texto_enter = "Presiona ENTER";
            Vector2 medida_enter = MeasureTextEx(GetFontDefault(), texto_enter, tamano_texto-20, espaciado_texto);
            float posX_enter = anchoPantalla / 2 - medida_enter.x / 2;
            float posY_enter = altoPantalla - 300;  // Más abajo

            DrawTextEx(GetFontDefault(), texto_enter, (Vector2){posX_enter - 100, posY_enter}, tamano_texto-20, espaciado_texto, YELLOW);
        }

        if (IsKeyPressed(KEY_ENTER)) {
            quetzal_se_va = true;
            quetzal_despidiendose = false;
            mensaje_quetzal_mostrado = 0;  // Ocultamos el mensaje de despedida
            iniciar_juego = true;
        }

        if (iniciar_juego) {
            vidas = 5;
            tiempo = 400;
            puntuacion = 0;
            monedas = 0;

            iniciar_juego = false;
        }
    }
}

//  Movimiento de Quetzalcóatl hacia la izquierda y salida
if (quetzal_se_va) {

    DrawTextureEx(textura_quetzalcoatl_actual, (Vector2){posX_quez, posY_quez}, 0.0f, 0.15f, WHITE);

    if (posX_quez + textura_quetzalcoatl_izquierda.width * 0.15f < 0) {
        quetzal_se_va = false;
        quetzal_despidiendose = false;
        en_cinematica_quetzal = false;
        mostrar_texto = 0;  // Comenzar juego con físicas normales
    }
}


    if (mostrar_texto == 2) {
        char mensaje_completo[100] = "Bienvenido a Ciudad de México";
        char mensaje_actual[100] = "";

        // Máquina de escribir
        if (mensaje_ciudad_mostrado == 0) {
            if (tiempo_inicio_ciudad == 0.0) {
                tiempo_inicio_ciudad = GetTime();  // Solo se inicializa al comenzar mensaje
            }

            float tiempo_actual = GetTime() - tiempo_inicio_ciudad;
            int longitud_deseada = (int)(tiempo_actual * 20.0f);
            if (longitud_deseada > strlen(mensaje_completo)) {
                longitud_deseada = strlen(mensaje_completo);
                mensaje_ciudad_mostrado = 1;
                StopSound(sonido_escribir);
            }
            else {
                if (!IsSoundPlaying(sonido_escribir)) {
                    PlaySound(sonido_escribir);  // Iniciar
                }
            }
            strncpy(mensaje_actual, mensaje_completo, longitud_deseada);
            mensaje_actual[longitud_deseada] = '\0';
        } else {
            strcpy(mensaje_actual, mensaje_completo);
        }

        // Configuración del cuadro de texto
        float margen = 30.0f;
        Vector2 dim_texto = MeasureTextEx(GetFontDefault(), mensaje_completo, tamano_texto-20, espaciado_texto);
        float cuadro_ancho = dim_texto.x + 30;
        float cuadro_alto = dim_texto.y + 20;
        float cuadro_posX = 100.0f;
        float cuadro_posY = 400.0f;

        DrawRectangle(cuadro_posX, cuadro_posY, cuadro_ancho, cuadro_alto, BLACK);
        DrawRectangleLines(cuadro_posX, cuadro_posY, cuadro_ancho, cuadro_alto, WHITE);
        DrawTextEx(GetFontDefault(), mensaje_actual, (Vector2){cuadro_posX + 15, cuadro_posY + 10},
                   tamano_texto-20, espaciado_texto, WHITE);

        // Mostrar "Presiona ENTER" cuando el mensaje esté completo
        if (mensaje_ciudad_mostrado == 1) {
            char texto_enter[] = "Presiona ENTER";
            Vector2 medida_enter = MeasureTextEx(GetFontDefault(), texto_enter, tamano_texto-20, espaciado_texto);
            float posX_enter = cuadro_posX + cuadro_ancho - medida_enter.x - 15;
            float posY_enter = cuadro_posY + cuadro_alto - medida_enter.y - 10;

            if (mostrar_texto_parpadeante == 1) {
                DrawTextEx(GetFontDefault(), texto_enter, (Vector2){posX_enter-15, posY_enter+50}, tamano_texto-20, espaciado_texto, YELLOW);
            }
        }

        if (IsKeyPressed(KEY_ENTER) && mensaje_ciudad_mostrado == 1) {
            mostrar_texto = 0;
                mostrar_fade_in_despedida = true;
            fade_despedida = 0.0f;
            tiempo_inicio_despedida = GetTime();
        }
    }
}

void Actualizar_fisicas(){


    if(estadoJuego== 1){
        limiteIzquierdo = 0.0f;
        limiteDerecho = anchoPantalla - 120.0f;
    }
    else if(estadoJuego == 5)
        limiteDerecho = (fondo1.width) - 120.0f;

    velX = 0.0f;

    // Movimiento horizontal solo si no está agachado
    if(estadoJuego == 1 || estadoJuego == 4 || estadoJuego == 5){
        if (agachado == 0) {
            // Movimiento hacia la derecha
            if (IsKeyDown(tecla_derecha) == true) {
                mirando_derecha = 1;
                if(IsKeyDown(tecla_correr) == true) // Correr o caminar
                    velX = 7.0f;
                else
                    velX = 4.0f;
                if(estadoJuego == 1 || estadoJuego == 4){
                    if (posX + velX > limiteDerecho)
                        velX = limiteDerecho - posX;
                }
            }
            // Movimiento hacia la izquierda
            else if (IsKeyDown(tecla_izquierda) == true) {
                mirando_derecha = 0;
                if(IsKeyDown(tecla_correr) == true) // Correr o caminar
                    velX = -7.0f;
                else
                    velX = -4.0f;

                    if (posX + velX < limiteIzquierdo)
                        velX = limiteIzquierdo - posX;


            }
        }
    }


    // Salto
    if (IsKeyPressed(tecla_salto) == true && saltando == 0 && agachado == 0) {
        PlaySound(sonido_salto);
        saltando = 1;
        tiempo_salto = 0.0f;
        velY = fuerza_Salto_extra;
    }

    // Aplicar gravedad según estado
    if (velY > 0.0f)
        // Jugador está cayendo
        gravedad = gravedad_caida;

    else if (IsKeyDown(tecla_salto) == true && saltando == 1) {
        // Jugador mantiene el salto presionado
        gravedad = gravedad_normal;

        // Aplicar fuerza de salto extra mientras se mantiene
        if (tiempo_salto < tiempo_max_salto) {
            velY += fuerza_Salto_extra * GetFrameTime();
            tiempo_salto += GetFrameTime();
        }
    }
    else
        // Caída normal o salto corto
        gravedad = gravedad_caida;

   // Mecánica de agacharse
if (IsKeyDown(tecla_agachar) == true && saltando == 0) {
    if (agachado == 0) {  // Solo ajustar posY si antes no estaba agachado
        float altura_normal = textura_actual.height * escala;
        float altura_agachado = textura_agachadoDerecha.height * escala; // Asume que ambas texturas agachadas tienen la misma altura
        posY += altura_normal - altura_agachado;  // Ajusta posY para compensar la diferencia
    }
    agachado = 1;
    if (IsKeyDown(tecla_derecha) == true) {
        mirando_derecha = 1;
        textura_actual = textura_agachadoDerecha;
    }
    else if (IsKeyDown(tecla_izquierda) == true) {
        mirando_derecha = 0;
        textura_actual = textura_agachadoIzquierda;
    }
    else {
        if (mirando_derecha == 1)
            textura_actual = textura_agachadoDerecha;
        else
            textura_actual = textura_agachadoIzquierda;
    }
}
else {
    if (agachado == 1) {  // Si estaba agachado y ahora se levanta
        float altura_agachado = textura_actual.height * escala;


    }
    agachado = 0;
}
    enSuelo = ActualizarColisiones();
    if(enSuelo == false)
        velY += gravedad;

    // Actualizar posición
    posX += velX;
    posY += velY;

    rectMauricio = (Rectangle){posX, posY, textura_actual.width * escala, textura_actual.height * escala};

    rectSuelo = (Rectangle){0.0f, 675.0f, 100000.0f, 20.0f};


    if (CheckCollisionRecs(rectMauricio, rectSuelo)) {
        if(agachado == 1)
            posY = 530.0f;
        else
            posY = 500.0f;
        velY = 0.0f;
        saltando = 0;  // Permitir que vuelva a saltar
        enSuelo = true;

    }

    else
        enSuelo = false;

    ActualizarColisiones();

    Rectangle rectPoli = {posX_poli + 25 , posY_poli, textura_poli_quieto_izquierda.width * escala_poli - 50 , textura_poli_quieto_izquierda.height * escala_poli};

if (posX_poli >= 0) { // Verifica que el poli no haya sido "eliminado"
    if (CheckCollision(rectMauricio, rectPoli)) {
        // Pisotón desde arriba
        if (velY > 0 && (rectMauricio.y + rectMauricio.height) < (rectPoli.y + 20)) {
            posX_poli = -1000; // Lo movemos fuera de pantalla permanentemente
            puntuacion += 100;
        }
    }
}

// Movimiento del policía

    if (estadoJuego == 5 && posX_poli >= -100) {  // Solo si está en pantalla o cerca
        posX_poli -= velocidad_poli;

        // Cambiar animación alternando entre quieto y caminando
        frame_poli++;
        if (frame_poli >= 20) {  // Ajusta la velocidad de alternancia
            frame_poli = 0;
            poli_caminando = !poli_caminando;
        }

        escala_poli = tamano_poli / textura_poli_quieto_izquierda.height;

        // Si sale completamente de pantalla por la izquierda, desactivarlo
        if (posX_poli + (textura_poli_quieto_izquierda.width * escala_poli) < 0) {
            posX_poli = -1000;

    }    }

}

void Actualizar_animaciones(){

    if(saltando == 1){
        if (mirando_derecha == 1)
            textura_actual = textura_saltoDerecha;
        else
            textura_actual = textura_saltoIzquierda;
    }

    if(velX != 0.0f && saltando == 0 && agachado == 0){
        frame_caminar++;
        if(frame_caminar >= 10){
            frame_caminar = 0;
            estado_caminar = (estado_caminar + 1) % 3;
        }

        if(mirando_derecha == 1){
            if(estado_caminar == 0)
                textura_actual = textura_jugadorDerecha;
            else if(estado_caminar == 1)
                textura_actual = textura_caminarDerecha1;
            else
                textura_actual = textura_caminarDerecha2;
        }
        else{
            if(estado_caminar == 0)
                textura_actual = textura_jugadorIzquierda;
            else if(estado_caminar == 1)
                textura_actual= textura_caminarIzquierda1;
            else
                textura_actual = textura_caminarIzquierda2;
        }
    }
    else if(saltando == 0 && agachado == 0){
        if(mirando_derecha == 1)
            textura_actual = textura_jugadorDerecha;
        else
            textura_actual = textura_jugadorIzquierda;
    }

    // Escalado de texturas
    if (agachado == 1)
        escala = tamano_agachado / textura_actual.height;
    else
        escala = tamano_normal / textura_actual.height;

}


void Actualizar_camara(){
    camara.target.x = posX;
    if (camara.target.x < anchoPantalla / 2)
        camara.target.x = anchoPantalla / 2;
}

void Actualizar_menu_principal(){
    tiempo_sel += GetFrameTime();
    if (IsKeyPressed(KEY_DOWN) == true || IsKeyPressed(KEY_S) == true)
        opc = (opc + 1) % num_opc;

    else if (IsKeyPressed(KEY_UP) == true || IsKeyPressed(KEY_W) == true)
        opc = (opc - 1 + num_opc) % num_opc;

    else if (IsKeyPressed(KEY_ENTER) == true) {
        Ejecutar_opcion();
        tiempo_sel = 0.0f;
    }
}

void Actualizar_menu_tutorial(){
    if (IsKeyPressed(KEY_RIGHT) == true || IsKeyPressed(KEY_D) == true) {
        if (opc == 2)
            opc = 1;
        else
            opc = 2;

    }

    else if (IsKeyPressed(KEY_LEFT) == true || IsKeyPressed(KEY_A) == true) {
        if (opc == 1)
            opc = 2;
        else
            opc = 1;

    }

    else if (IsKeyPressed(KEY_ENTER) == true) {
        if(opc == 1){
            estadoJuego = 4;
            mostrar_texto = 1;
            posX = (anchoPantalla / 2) - 70;
            // Inicializar variables del tutorial
            paso_tutorial = 0;
            mensaje_completo_mostrado = 0;
            tiempo_inicio_tutorial = GetTime();
            tecla_presionada_tutorial = 0;
            tutorial_completo = false;
        }
        else{
            estadoJuego = 5;
            mostrar_texto = 2;
        }
    }
}

void Ejecutar_opcion(){


        switch (opc) {
           case Iniciar_Partida:
        ReiniciarJuego();
        estadoJuego = 3;
        opc = 1;
        tiempo_sel = 0.0f;
        break;
            case Cargar_Partida:
                CargarPartida();
                tiempo_sel = 0.0f;
                break;
            case Opciones:
                estadoJuego = 7;
                break;
            case Salir:
                CloseWindow();
                break;
        }
    }


// Función auxiliar para detectar colisión entre rectángulos
bool Colisiona(Rectangle a, Rectangle b) {
    return !(a.x + a.width <= b.x ||
             b.x + b.width <= a.x ||
             a.y + a.height <= b.y ||
             b.y + b.height <= a.y);
}

bool PuedeColocarBloque(Rectangle nuevoRect, int numBloquesActuales, Bloque bloques[]) {
    for (int i = 0; i < numBloquesActuales; i++) {
        if (Colisiona(nuevoRect, bloques[i].rect)) {
            return false;
        }
    }
    return true;
}

void InicializarBloques() {
    int idx = 0;
    float inicioX = 600.0f;
    float inicioY = 400.0f;
    float saltoX = bloque.width * 0.025f; // tomar tamaño real escalado para no superponer
    float saltoPatron = 200.0f;
    float alturaObjeto = 150.0f;

    float escala = 0.025f;

    // Limpiar bloques
    for (int i = 0; i < num_bloques; i++) {
        bloques[i].recolectado = 0;
        bloques[i].item_activo = 0;
        bloques[i].bloque_roto = false;
        bloques[i].tipo = BLOQUE_VACIO;
    }

    float posXActual = inicioX;
    int patronContador = 0;
    bool escalera_colocada = false;
    bool escalera_invertida_colocada = false;

    while (idx < num_bloques) {
        switch (patronContador % 12) {  // Ahora 12 patrones
            case 0:  // 3 bloques normales en línea
                for (int b = 0; b < 3 && idx < num_bloques; b++) {
                    bloques[idx].posX = posXActual + b * saltoX;
                    bloques[idx].posY = inicioY;
                    bloques[idx].tipo = BLOQUE_NORMAL;
                    bloques[idx].escala = escala;
                    bloques[idx].item_activo = 0;
                    bloques[idx].recolectado = 0;
                    bloques[idx].bloque_roto = false;
                    bloques[idx].rect = (Rectangle){
                        bloques[idx].posX,
                        bloques[idx].posY,
                        bloque.width * escala,
                        bloque.height * escala
                    };
                    idx++;
                }
                posXActual += 3 * saltoX + saltoPatron;
                break;

            case 1:  // 1 bloque objeto arriba
                if (idx < num_bloques) {
                    bloques[idx].posX = posXActual + saltoX;
                    bloques[idx].posY = inicioY - alturaObjeto;
                    bloques[idx].tipo = BLOQUE_OBJETO;
                    bloques[idx].escala = escala;
                    bloques[idx].item_activo = 0;
                    bloques[idx].recolectado = 0;
                    bloques[idx].bloque_roto = false;
                    bloques[idx].rect = (Rectangle){
                        bloques[idx].posX,
                        bloques[idx].posY,
                        bloque.width * escala,
                        bloque.height * escala
                    };
                    idx++;
                }
                posXActual += saltoX + saltoPatron;
                break;

            case 2:  // 2 bloques normales en línea
                for (int b = 0; b < 2 && idx < num_bloques; b++) {
                    bloques[idx].posX = posXActual + b * saltoX;
                    bloques[idx].posY = inicioY;
                    bloques[idx].tipo = BLOQUE_NORMAL;
                    bloques[idx].escala = escala;
                    bloques[idx].item_activo = 0;
                    bloques[idx].recolectado = 0;
                    bloques[idx].bloque_roto = false;
                    bloques[idx].rect = (Rectangle){
                        bloques[idx].posX,
                        bloques[idx].posY,
                        bloque.width * escala,
                        bloque.height * escala
                    };
                    idx++;
                }
                posXActual += 2 * saltoX + saltoPatron;
                break;

            case 3:  // vacío
                posXActual += saltoPatron;
                break;

            case 4:  // 4 bloques normales en línea
                for (int b = 0; b < 4 && idx < num_bloques; b++) {
                    bloques[idx].posX = posXActual + b * saltoX;
                    bloques[idx].posY = inicioY;
                    bloques[idx].tipo = BLOQUE_NORMAL;
                    bloques[idx].escala = escala;
                    bloques[idx].item_activo = 0;
                    bloques[idx].recolectado = 0;
                    bloques[idx].bloque_roto = false;
                    bloques[idx].rect = (Rectangle){
                        bloques[idx].posX,
                        bloques[idx].posY,
                        bloque.width * escala,
                        bloque.height * escala
                    };
                    idx++;
                }
                posXActual += 4 * saltoX + saltoPatron;
                break;

            case 5:  // patrón escalera (solo 1 vez)
                if (!escalera_colocada) {
                    for (int b = 0; b < 5 && idx < num_bloques; b++) {
                        bloques[idx].posX = posXActual + b * saltoX;
                        bloques[idx].posY = inicioY - b * (bloque.height * escala / 2);
                        bloques[idx].tipo = BLOQUE_NORMAL;
                        bloques[idx].escala = escala;
                        bloques[idx].item_activo = 0;
                        bloques[idx].recolectado = 0;
                        bloques[idx].bloque_roto = false;
                        bloques[idx].rect = (Rectangle){
                            bloques[idx].posX,
                            bloques[idx].posY,
                            bloque.width * escala,
                            bloque.height * escala
                        };
                        idx++;
                    }
                    for (int b = 1; b < 5 && idx < num_bloques; b++) {
                        bloques[idx].posX = posXActual + (4 + b) * saltoX;
                        bloques[idx].posY = inicioY - (5 - b) * (bloque.height * escala / 2);
                        bloques[idx].tipo = BLOQUE_NORMAL;
                        bloques[idx].escala = escala;
                        bloques[idx].item_activo = 0;
                        bloques[idx].recolectado = 0;
                        bloques[idx].bloque_roto = false;
                        bloques[idx].rect = (Rectangle){
                            bloques[idx].posX,
                            bloques[idx].posY,
                            bloque.width * escala,
                            bloque.height * escala
                        };
                        idx++;
                    }
                    posXActual += 10 * saltoX + saltoPatron;
                    escalera_colocada = true;
                } else {
                    posXActual += saltoPatron + 5 * saltoX;
                }
                break;

            case 6:  // "L" invertida (3 base + 2 arriba a la derecha)
                if (idx + 5 <= num_bloques) {
                    // Base 3 bloques
                    for (int b = 0; b < 3; b++) {
                        bloques[idx].posX = posXActual + b * saltoX;
                        bloques[idx].posY = inicioY;
                        bloques[idx].tipo = BLOQUE_NORMAL;
                        bloques[idx].escala = escala;
                        bloques[idx].item_activo = 0;
                        bloques[idx].recolectado = 0;
                        bloques[idx].bloque_roto = false;
                        bloques[idx].rect = (Rectangle){
                            bloques[idx].posX,
                            bloques[idx].posY,
                            bloque.width * escala,
                            bloque.height * escala
                        };
                        idx++;
                    }
                    // 2 bloques arriba extremos derecha
                    for (int b = 0; b < 2; b++) {
                        bloques[idx].posX = posXActual + 2 * saltoX;
                        bloques[idx].posY = inicioY - (b + 1) * (bloque.height * escala);
                        bloques[idx].tipo = BLOQUE_NORMAL;
                        bloques[idx].escala = escala;
                        bloques[idx].item_activo = 0;
                        bloques[idx].recolectado = 0;
                        bloques[idx].bloque_roto = false;
                        bloques[idx].rect = (Rectangle){
                            bloques[idx].posX,
                            bloques[idx].posY,
                            bloque.width * escala,
                            bloque.height * escala
                        };
                        idx++;
                    }
                    posXActual += 3 * saltoX + saltoPatron;
                } else {
                    // Si no hay espacio suficiente, avanzar sin poner bloques
                    posXActual += saltoPatron;
                }
                break;

            case 7:  // "T" (3 base + 1 arriba centro)
                if (idx + 4 <= num_bloques) {
                    // Base 3 bloques
                    for (int b = 0; b < 3; b++) {
                        bloques[idx].posX = posXActual + b * saltoX;
                        bloques[idx].posY = inicioY;
                        bloques[idx].tipo = BLOQUE_NORMAL;
                        bloques[idx].escala = escala;
                        bloques[idx].item_activo = 0;
                        bloques[idx].recolectado = 0;
                        bloques[idx].bloque_roto = false;
                        bloques[idx].rect = (Rectangle){
                            bloques[idx].posX,
                            bloques[idx].posY,
                            bloque.width * escala,
                            bloque.height * escala
                        };
                        idx++;
                    }
                    // Bloque arriba en centro
                    bloques[idx].posX = posXActual + saltoX;
                    bloques[idx].posY = inicioY - bloque.height * escala;
                    bloques[idx].tipo = BLOQUE_NORMAL;
                    bloques[idx].escala = escala;
                    bloques[idx].item_activo = 0;
                    bloques[idx].recolectado = 0;
                    bloques[idx].bloque_roto = false;
                    bloques[idx].rect = (Rectangle){
                        bloques[idx].posX,
                        bloques[idx].posY,
                        bloque.width * escala,
                        bloque.height * escala
                    };
                    idx++;
                    posXActual += 3 * saltoX + saltoPatron;
                } else {
                    posXActual += saltoPatron;
                }
                break;

            case 8:  // "U" (3 base + 2 arriba extremos)
                if (idx + 5 <= num_bloques) {
                    for (int b = 0; b < 3; b++) {
                        bloques[idx].posX = posXActual + b * saltoX;
                        bloques[idx].posY = inicioY;
                        bloques[idx].tipo = BLOQUE_NORMAL;
                        bloques[idx].escala = escala;
                        bloques[idx].item_activo = 0;
                        bloques[idx].recolectado = 0;
                        bloques[idx].bloque_roto = false;
                        bloques[idx].rect = (Rectangle){
                            bloques[idx].posX,
                            bloques[idx].posY,
                            bloque.width * escala,
                            bloque.height * escala
                        };
                        idx++;
                    }
                    // Bloques arriba en extremos izquierda y derecha
                    bloques[idx].posX = posXActual;
                    bloques[idx].posY = inicioY - bloque.height * escala;
                    bloques[idx].tipo = BLOQUE_NORMAL;
                    bloques[idx].escala = escala;
                    bloques[idx].item_activo = 0;
                    bloques[idx].recolectado = 0;
                    bloques[idx].bloque_roto = false;
                    bloques[idx].rect = (Rectangle){
                        bloques[idx].posX,
                        bloques[idx].posY,
                        bloque.width * escala,
                        bloque.height * escala
                    };
                    idx++;

                    bloques[idx].posX = posXActual + 2 * saltoX;
                    bloques[idx].posY = inicioY - bloque.height * escala;
                    bloques[idx].tipo = BLOQUE_NORMAL;
                    bloques[idx].escala = escala;
                    bloques[idx].item_activo = 0;
                    bloques[idx].recolectado = 0;
                    bloques[idx].bloque_roto = false;
                    bloques[idx].rect = (Rectangle){
                        bloques[idx].posX,
                        bloques[idx].posY,
                        bloque.width * escala,
                        bloque.height * escala
                    };
                    idx++;
                    posXActual += 3 * saltoX + saltoPatron;
                } else {
                    posXActual += saltoPatron;
                }
                break;

            case 9:  // Escalera invertida (solo 1 vez)
                if (!escalera_invertida_colocada) {
                    // Escalera descendente
                    for (int b = 0; b < 5 && idx < num_bloques; b++) {
                        bloques[idx].posX = posXActual + b * saltoX;
                        bloques[idx].posY = inicioY - (4 - b) * (bloque.height * escala / 2);
                        bloques[idx].tipo = BLOQUE_NORMAL;
                        bloques[idx].escala = escala;
                        bloques[idx].item_activo = 0;
                        bloques[idx].recolectado = 0;
                        bloques[idx].bloque_roto = false;
                        bloques[idx].rect = (Rectangle){
                            bloques[idx].posX,
                            bloques[idx].posY,
                            bloque.width * escala,
                            bloque.height * escala
                        };
                        idx++;
                    }
                    // Escalera ascendente
                    for (int b = 1; b < 5 && idx < num_bloques; b++) {
                        bloques[idx].posX = posXActual + (4 + b) * saltoX;
                        bloques[idx].posY = inicioY - b * (bloque.height * escala / 2);
                        bloques[idx].tipo = BLOQUE_NORMAL;
                        bloques[idx].escala = escala;
                        bloques[idx].item_activo = 0;
                        bloques[idx].recolectado = 0;
                        bloques[idx].bloque_roto = false;
                        bloques[idx].rect = (Rectangle){
                            bloques[idx].posX,
                            bloques[idx].posY,
                            bloque.width * escala,
                            bloque.height * escala
                        };
                        idx++;
                    }
                    posXActual += 10 * saltoX + saltoPatron;
                    escalera_invertida_colocada = true;
                } else {
                    posXActual += saltoPatron + 5 * saltoX;
                }
                break;

            case 10:  // Lineal 6 bloques juntos
                if (idx + 6 <= num_bloques) {
                    for (int b = 0; b < 6; b++) {
                        bloques[idx].posX = posXActual + b * saltoX;
                        bloques[idx].posY = inicioY;
                        bloques[idx].tipo = BLOQUE_NORMAL;
                        bloques[idx].escala = escala;
                        bloques[idx].item_activo = 0;
                        bloques[idx].recolectado = 0;
                        bloques[idx].bloque_roto = false;
                        bloques[idx].rect = (Rectangle){
                            bloques[idx].posX,
                            bloques[idx].posY,
                            bloque.width * escala,
                            bloque.height * escala
                        };
                        idx++;
                    }
                    posXActual += 6 * saltoX + saltoPatron;
                } else {
                    posXActual += saltoPatron;
                }
                break;

            case 11:  // 1 bloque objeto solo, arriba un poco
                if (idx < num_bloques) {
                    bloques[idx].posX = posXActual;
                    bloques[idx].posY = inicioY - alturaObjeto;
                    bloques[idx].tipo = BLOQUE_OBJETO;
                    bloques[idx].escala = escala;
                    bloques[idx].item_activo = 0;
                    bloques[idx].recolectado = 0;
                    bloques[idx].bloque_roto = false;
                    bloques[idx].rect = (Rectangle){
                        bloques[idx].posX,
                        bloques[idx].posY,
                        bloque.width * escala,
                        bloque.height * escala
                    };
                    idx++;
                }
                posXActual += saltoX + saltoPatron;
                break;
        }
        patronContador++;
    }
}

bool CheckCollision(Rectangle rec1, Rectangle rec2) {
    return (rec1.x < rec2.x + rec2.width &&rec1.x + rec1.width > rec2.x &&rec1.y < rec2.y + rec2.height && rec1.y + rec1.height > rec2.y);
}


bool ActualizarColisiones() {
    // Ajusta el rectángulo de colisión del jugador con márgenes para mejor detección
    rectMauricio = (Rectangle){posX + 25, posY - 20, textura_actual.width * escala - 50, textura_actual.height * escala - 15};
    float margen_desaparicion = 200.0f;

    float mundoMinX = camara.target.x - anchoPantalla / 2 - margen_desaparicion;
    float mundoMaxX = camara.target.x + anchoPantalla / 2 + margen_desaparicion;

    enSuelo = false;

    // Variables para acumulación de correcciones
    float correccionLateral = 0.0f;
    float minPenetrationX = 1e9f; // Valor muy alto para comparar mínimos
    bool hayColisionLateral = false;

    bool hayColisionVertical = false;
    float penetrationYMin = 1e9f;
    float correccionVertical = 0.0f;

    if (estadoJuego == 5) {
        for (int i = 0; i < num_bloques; i++) {
            // Ignorar bloques normales o vacíos que ya estén rotos
            if ((bloques[i].tipo == BLOQUE_VACIO || bloques[i].tipo == BLOQUE_NORMAL) && bloques[i].bloque_roto)
                continue;

            // Actualizar rectángulo del bloque
            bloques[i].rect = (Rectangle){
                bloques[i].posX,
                bloques[i].posY,
                bloque.width * bloques[i].escala,
                bloque.height * bloques[i].escala
            };

            if (CheckCollisionRecs(rectMauricio, bloques[i].rect)) {
                // Calcular la penetración en cada dirección
                float overlapLeft   = rectMauricio.x + rectMauricio.width - bloques[i].rect.x;
                float overlapRight  = bloques[i].rect.x + bloques[i].rect.width - rectMauricio.x;
                float overlapTop    = rectMauricio.y + rectMauricio.height - bloques[i].rect.y;
                float overlapBottom = bloques[i].rect.y + bloques[i].rect.height - rectMauricio.y;

                float penetrationX = (overlapLeft < overlapRight) ? -overlapLeft : overlapRight;
                float penetrationY = (overlapTop < overlapBottom) ? -overlapTop : overlapBottom;

                // Priorizar la corrección vertical si es menor que la lateral
                if (fabsf(penetrationY) < fabsf(penetrationX)) {
                    hayColisionVertical = true;
                    if (fabsf(penetrationY) < penetrationYMin) {
                        penetrationYMin = fabsf(penetrationY);
                        correccionVertical = penetrationY;
                    }

                    // Si es colisión desde arriba (caída sobre bloque)
                    if (penetrationY < 0) {
                        saltando = 0;
                        enSuelo = true;
                    }

                } else {
                    // Almacenar corrección lateral mínima (más cercana)
                    if (fabsf(penetrationX) < minPenetrationX) {
                        minPenetrationX = fabsf(penetrationX);
                        correccionLateral = penetrationX;
                        hayColisionLateral = true;
                    }
                }

                // Si colisiona desde abajo (golpe al bloque)
                if (penetrationY > 0) {
                    posY += penetrationY;
                    velY = 0;

                    if (bloques[i].item_activo == 0 && bloques[i].recolectado == 0) {
                        PlaySound(item);
                        bloques[i].item_activo = 1;
                        bloques[i].posX_item = bloques[i].posX + (bloque.width * bloques[i].escala) / 2 - radio_item + 20;
                        bloques[i].posY_item = bloques[i].posY - radio_item * 2;
                        bloques[i].velocidad_item_Y = -2.0f;
                    }

                    if (bloques[i].tipo == BLOQUE_VACIO || bloques[i].tipo == BLOQUE_NORMAL) {
                        bloques[i].bloque_roto = true;
                    }
                }
            }
        }
    }

    // Aplicar corrección vertical si hay colisión vertical
    if (hayColisionVertical) {
        posY += correccionVertical;
        velY = 0;
    }
    // Solo aplicar corrección lateral si no hay colisión vertical
    else if (hayColisionLateral) {
        posX += correccionLateral;
        velX = 0;
    }

    // Actualizar y manejar movimiento de ítems
    for (int i = 0; i < num_bloques; i++) {
        if (bloques[i].item_activo > 0) {
            if (bloques[i].item_activo == 1) {
                bloques[i].velocidad_item_Y += gravedad_item;
                bloques[i].posY_item += bloques[i].velocidad_item_Y;

                if (bloques[i].posY_item + radio_item >= 650.0f) {
                    bloques[i].posY_item = 650.0f - radio_item;
                    bloques[i].velocidad_item_Y = 0;
                    bloques[i].item_activo = 2;
                }
            } else if (bloques[i].item_activo == 2) {
                bloques[i].posX_item += bloques[i].velocidad_item_X;

                if (bloques[i].posX_item + radio_item < mundoMinX ||
                    bloques[i].posX_item - radio_item > mundoMaxX) {
                    bloques[i].item_activo = 0;
                    bloques[i].recolectado = 1;
                }
            }

            // Recolectar ítem si colisiona con el jugador
            Rectangle rectItem = {
                bloques[i].posX_item - radio_item,
                bloques[i].posY_item - radio_item,
                radio_item * 2,
                radio_item * 2
            };

            if (CheckCollisionRecs(rectMauricio, rectItem)) {
                bloques[i].item_activo = 0;
                bloques[i].recolectado = 1;
                puntuacion += 1000;
                PlaySound(power_up);
            }
        }
    }

    return enSuelo;
}


void Actualizar_quetzalcoatl() {
    // Si está caminando (llegando o despidiéndose)
    if (quetzal_se_va || !quetzal_llego) {
        // Animar siempre caminata
        frame_camina_quetz++;
        if (frame_camina_quetz >= 10) {
            frame_camina_quetz = 0;
            estado_camina_quetz = !estado_camina_quetz;
        }

        if (estado_camina_quetz == 0)
            textura_quetzalcoatl_actual = textura_quetzalcoatl_caminado_izquierda;
        else
            textura_quetzalcoatl_actual = textura_quetzalcoatl_izquierda;

        // Movimiento horizontal
        if (quetzal_se_va)
            posX_quez += velX_quetzal_despedida;  // camina hacia fuera
        else
            posX_quez -= velX_quez;               // camina hacia dentro

        // Si terminó la despedida (fuera de pantalla)
        if (quetzal_se_va && posX_quez + textura_quetzalcoatl_actual.width * 0.15f < 0) {
            quetzal_se_va = false;
            quetzal_despidiendose = false;
            quetzal_llego = false;
            paso_mensaje_quetzal = 0;
            mensaje_quetzal_mostrado = 0;
            tiempo_inicio_quetzal = 0.0f;
            mostrar_texto = 0;
            hud_mostrar = true;

             posX_poli = 1500.0f;   // Vuelve a posición inicial
             posY_poli = 520;
        }

        // Si terminó de llegar
        if (!quetzal_se_va && !quetzal_llego && posX_quez <= posX + 200.0f) {
            quetzal_llego = true;
        }
    }
    else {
        // Está quieto en su posición
        textura_quetzalcoatl_actual = textura_quetzalcoatl_izquierda;
    }
}


void Actualizar_menu_pausa() {
    if (IsKeyPressed(KEY_S)) {
        opcionPausa = (opcionPausa + 1) % NUM_OPCIONES_PAUSA;
    } else if (IsKeyPressed(KEY_W)) {
        opcionPausa = (opcionPausa - 1 + NUM_OPCIONES_PAUSA) % NUM_OPCIONES_PAUSA;
    } else if (IsKeyPressed(KEY_ENTER)) {
        switch (opcionPausa) {
            case CONTINUAR_PARTIDA:
                juegoPausado = false;
                estadoJuego = 5;  // Volver al juego
                ResumeMusicStream(level1_music);
                break;

            case GUARDAR_PARTIDA:
                GuardarPartida();
                break;

            case MENU_PRINCIPAL_PAUSA:
                juegoPausado = false;
                estadoJuego = 2; // Ir al menú principal
                StopMusicStream(level1_music);
                ReiniciarJuego();
                break;

            case SALIR_PAUSA:
                CloseWindow();
                break;
        }
    }
}

bool mensaje_guardado = false;
float tiempo_guardado = 0.0f;

void GuardarPartida() {
    FILE *archivo = fopen("partida_guardada.dat", "wb");
    if (archivo != NULL) {
        fwrite(&posX, sizeof(float), 1, archivo);
        fwrite(&posY, sizeof(float), 1, archivo);
        fwrite(&vidas, sizeof(int), 1, archivo);
        fwrite(&puntuacion, sizeof(int), 1, archivo);
        fwrite(&tiempo, sizeof(int), 1, archivo);
        fwrite(&monedas, sizeof(int), 1, archivo);
        for (int i = 0; i < num_bloques; i++)
            fwrite(&bloques[i].recolectado, sizeof(int), 1, archivo);
        fwrite(&posX_quez, sizeof(float), 1, archivo);
        fwrite(&quetzal_llego, sizeof(bool), 1, archivo);
        fwrite(&en_cinematica_quetzal, sizeof(bool), 1, archivo);
        fwrite(&paso_mensaje_quetzal, sizeof(int), 1, archivo);
        fwrite(&mensaje_quetzal_mostrado, sizeof(int), 1, archivo);
        fwrite(&mostrar_texto, sizeof(int), 1, archivo);
        fwrite(&mensaje_ciudad_mostrado, sizeof(int), 1, archivo);
        fwrite(&mostrar_flashback, sizeof(bool), 1, archivo);
        // Puedes guardar temporizadores si quieres para reanudar más preciso
        fclose(archivo);

        mensaje_guardado = true;
        tiempo_guardado = GetTime();
    }
}

void CargarPartida() {
    FILE *archivo = fopen("partida_guardada.dat", "rb");
    if (archivo != NULL) {
        fread(&posX, sizeof(float), 1, archivo);
        fread(&posY, sizeof(float), 1, archivo);
        fread(&vidas, sizeof(int), 1, archivo);
        fread(&puntuacion, sizeof(int), 1, archivo);
        fread(&tiempo, sizeof(int), 1, archivo);
        fread(&monedas, sizeof(int), 1, archivo);
        for (int i = 0; i < num_bloques; i++) {
            fread(&bloques[i].recolectado, sizeof(int), 1, archivo);
            bloques[i].item_activo = 0;
        }
        fread(&posX_quez, sizeof(float), 1, archivo);
        fread(&quetzal_llego, sizeof(bool), 1, archivo);
        fread(&en_cinematica_quetzal, sizeof(bool), 1, archivo);
        fread(&paso_mensaje_quetzal, sizeof(int), 1, archivo);
        fread(&mensaje_quetzal_mostrado, sizeof(int), 1, archivo);
        fread(&mostrar_texto, sizeof(int), 1, archivo);
        fread(&mensaje_ciudad_mostrado, sizeof(int), 1, archivo);
        fread(&mostrar_flashback, sizeof(bool), 1, archivo);
        fclose(archivo);

        // Si estás en alguna cinemática o texto, poner estado adecuado
        if (en_cinematica_quetzal) {
            estadoJuego = 5;  // Juego con cinemática Quetzalcoatl activa
        } else if (mostrar_texto == 1) {
            estadoJuego = 4;  // Tutorial
        } else {
            estadoJuego = 5;  // Juego normal
        }

        juegoPausado = false;
        StopMusicStream(musica);
        PlayMusicStream(level1_music);

        camara.target.x = posX;
        if (camara.target.x < anchoPantalla / 2)
            camara.target.x = anchoPantalla / 2;

        // Resetear temporizadores para que máquina de escribir inicie bien
        tiempo_inicio_quetzal = 0.0f;
        tiempo_inicio_ciudad = 0.0f;
        tiempo_inicio_flashback = 0.0f;
        tiempo_inicio_mensaje_flashback = 0.0f;
        tiempo_inicio_tutorial = 0.0f;

        PollInputEvents();

        if (estadoJuego == 5 && !en_cinematica_quetzal && !mostrar_texto) {
            hud_mostrar = true;
        } else {
            hud_mostrar = false;
        }
    }
}



void Dibujar_menu_pausa() {

    DrawTexture(fondo1, 0, 0, DARKGRAY);

    // Título con sombra
    char* titulo = "PAUSA";
    int tamTitulo = 50;
    int sombraDespl = 2;
    int anchoTitulo = MeasureText(titulo, tamTitulo);
    int posXtitulo = anchoPantalla/2 - anchoTitulo/2;
    int posYtitulo = 150;

    DrawText(titulo, posXtitulo + sombraDespl, posYtitulo + sombraDespl, tamTitulo, BLACK);  // sombra
    DrawText(titulo, posXtitulo, posYtitulo, tamTitulo, WHITE);                            // texto principal

    char* opciones[NUM_OPCIONES_PAUSA] = {
        "Continuar partida",
        "Guardar partida",
        "Menu principal",
        "Salir del juego"
    };

    for (int i = 0; i < NUM_OPCIONES_PAUSA; i++) {
        int tamOpc = 30;
        int posY = 250 + i * 50;
        int anchoOpc = MeasureText(opciones[i], tamOpc);
        int posX = anchoPantalla/2 - anchoOpc/2;
        Color color = (i == opcionPausa) ? YELLOW : WHITE;

        // Sombra
        DrawText(opciones[i], posX + sombraDespl, posY + sombraDespl, tamOpc, BLACK);
        // Texto principal
        DrawText(opciones[i], posX, posY, tamOpc, color);
    }


    if (mensaje_guardado) {
        // Aquí podrías agregar algo si quieres
    }
    if (GetTime() - tiempo_guardado < 2.0f) {  // Mostrar por 2 segundos
        const char* msg = "Partida guardada con exito!";
        int tamMsg = 20;
        int anchoMsg = MeasureText(msg, tamMsg);
        int posXmsg = anchoPantalla/2 - anchoMsg/2;
        int posYmsg = 500;

        DrawText(msg, posXmsg + sombraDespl, posYmsg + sombraDespl, tamMsg, BLACK);
        DrawText(msg, posXmsg, posYmsg, tamMsg, GREEN);
    } else {
        mensaje_guardado = false;  // Ocultar mensaje
    }

    char* pie = "Usa W y S para navegar y ENTER para seleccionar";
    Vector2 medidaPie = MeasureTextEx(GetFontDefault(), pie, 20, 2);
    int posXpie = (anchoPantalla - medidaPie.x)/2;
    int posYpie = altoPantalla - 40;

    DrawTextEx(GetFontDefault(), pie, (Vector2){posXpie + sombraDespl, posYpie + sombraDespl}, 20, 2, Fade(BLACK, difuminado));
    DrawTextEx(GetFontDefault(), pie, (Vector2){posXpie, posYpie}, 20, 2, Fade(LIGHTGRAY, difuminado));
}

void ReiniciarJuego() {
    // --- Posiciones y estados principales ---
    posX = 0.0f;
    posY = 500.0f;
    vidas = 5;
    puntuacion = 0;
    tiempo = 400;
    monedas = 0;

    for (int i = 0; i < num_bloques; i++) {
        bloques[i].recolectado = 0;
        bloques[i].item_activo = 0;
    }

    posX_poli = 1500.0f;
    posY_poli = 520.0f;
    poli_caminando = 0;
    frame_poli = 0;

    hud_mostrar = false;

    // --- Reiniciar variables de Quetzalcóatl ---
    posX_quez = 1300.0f; // Posición fuera de pantalla derecha (no visible)
    posY_quez = 460.0f;
    quetzal_llego = false;
    en_cinematica_quetzal = false;
    quetzal_se_va = false;
    quetzal_despidiendose = false;
    paso_mensaje_quetzal = 0;
    velX_quetzal_despedida = -2.0f;
    textura_quetzalcoatl_actual = textura_quetzalcoatl_izquierda;

    // --- Reiniciar estados de texto / máquina de escribir ---
    mensaje_completo_mostrado = 0;
    mensaje_quetzal_mostrado = 0;
    mensaje_ciudad_mostrado = 0;
    mensaje_flashback_mostrado = 0;
    mensaje_guardado = false;

    // --- Detener sonido de escritura si está activo ---
    if (IsSoundPlaying(sonido_escribir))
        StopSound(sonido_escribir);

    // --- Resetear temporizadores ---
    tiempo_inicio_tutorial = 0.0f;
    tiempo_inicio_quetzal = 0.0f;
    tiempo_inicio_ciudad = 0.0f;
    tiempo_inicio_flashback = 0.0f;
    tiempo_inicio_mensaje_flashback = 0.0f;

    // --- Más variables si quieres ---
    iniciar_fade_out = false;
    fade_out_tutorial = 0.0f;
    mostrar_flashback = false;
    fade_flashback = 0.0f;
    tiempo_fin_tutorial = 0.0f;
    fade_despedida = 0.0f;
    mostrar_fade_in_despedida = false;

    // --- Configuración cámara y texturas ---
    camara.target.x = anchoPantalla / 2;
    camara.target.y = altoPantalla / 2;

    mirando_derecha = 1;
    textura_actual = textura_jugadorDerecha;
    escala = tamano_normal / textura_actual.height;

    opcionPausa = 0;
    juegoPausado = false;
}

void actualizarMenuOpciones() {
    if (!esperando_tecla) {
        if (IsKeyPressed(KEY_ONE)) {
                tecla_remapeando = 1; esperando_tecla = true;
                }
        if (IsKeyPressed(KEY_TWO)) {
            tecla_remapeando = 2; esperando_tecla = true;
            }
        if (IsKeyPressed(KEY_THREE)) {
            tecla_remapeando = 3; esperando_tecla = true;
            }
        if (IsKeyPressed(KEY_FOUR)) {
            tecla_remapeando = 4; esperando_tecla = true;
            }
        if (IsKeyPressed(KEY_FIVE)) {
            tecla_remapeando = 5; esperando_tecla = true;
            }
        if (IsKeyPressed(KEY_SIX)) {
            tecla_remapeando = 6; esperando_tecla = true;
        }
    }
    else {
        for (int k = 32; k < 349; k++) {
            if (IsKeyPressed(k)) {
                if (!teclaAsignada(k)) {  // solo asignar si no está usada
                    switch (tecla_remapeando) {
                        case 1:
                            tecla_izquierda = k;
                            break;
                        case 2:
                            tecla_derecha = k;
                            break;
                        case 3:
                            tecla_salto = k;
                            break;
                        case 4:
                            tecla_agachar = k;
                            break;
                        case 5:
                            tecla_correr = k;
                            break;
                    }
                    esperando_tecla = false;
                    tecla_remapeando = 0;
                    mostrarMensajeTeclaUsada = false;
                    tiempoMensajeTeclaUsada = 0;
                }
                else {
                    mostrarMensajeTeclaUsada = true;
                    tiempoMensajeTeclaUsada = 120;
                }
            }
        }
    }

    if (mostrarMensajeTeclaUsada) {
        tiempoMensajeTeclaUsada--;
        if (tiempoMensajeTeclaUsada <= 0) {
            mostrarMensajeTeclaUsada = false;
        }
    }

    if (!esperando_tecla && tecla_remapeando == 0) {
        if (estadoJuego == 7) {  // asegúrate de que sea el estado correcto
            if (IsKeyDown(KEY_UP)) {
                volumenJuego += 0.01f;
                if (volumenJuego > 1.0f) volumenJuego = 1.0f;
                SetMasterVolume(volumenJuego);  // ajusta volumen general
            }
            if (IsKeyDown(KEY_DOWN)) {
                volumenJuego -= 0.01f;
                if (volumenJuego < 0.0f) volumenJuego = 0.0f;
                SetMasterVolume(volumenJuego);
            }
        }
    }

    mostrar_texto_parpadeante++;
    if (mostrar_texto_parpadeante > 60) mostrar_texto_parpadeante = 0;

    if (IsKeyPressed(KEY_BACKSPACE)) {
        PollInputEvents();

        estadoJuego = 2;  // volver al menú principal
    }
}


void dibujarMenuOpciones() {
    ClearBackground(BLACK);
    DrawTexture(fondo1, 0, 0, DARKGRAY);

    // Título principal
    int centroX = 650;
    DrawText("OPCIONES", centroX - MeasureText("OPCIONES", 50)/2, 50, 50, WHITE);

    // --- Sección Controles ---
    DrawText("CONTROLES", centroX - MeasureText("CONTROLES", 30)/2, 120, 30, SKYBLUE);

    // Dibujar líneas separadoras
    DrawLine(centroX - 150, 160, centroX + 150, 160, SKYBLUE);

    // Opciones controles
    DrawText(TextFormat("1. Izquierda: %s", nombreTecla(tecla_izquierda)), centroX - 140, 190, 20, WHITE);
    DrawText(TextFormat("2. Derecha: %s", nombreTecla(tecla_derecha)), centroX - 140, 230, 20, WHITE);
    DrawText(TextFormat("3. Saltar: %s", nombreTecla(tecla_salto)), centroX - 140, 270, 20, WHITE);
    DrawText(TextFormat("4. Agacharse: %s", nombreTecla(tecla_agachar)), centroX - 140, 310, 20, WHITE);
    DrawText(TextFormat("5. Correr: %s", nombreTecla(tecla_correr)), centroX - 140, 350, 20, WHITE);

    // --- Sección Audio ---
    DrawText("AUDIO", centroX - MeasureText("AUDIO", 30)/2, 410, 30, ORANGE);
    DrawLine(centroX - 150, 450, centroX + 150, 450, ORANGE);

    DrawText(TextFormat("Volumen: %d%%", (int)(volumenJuego * 100)), centroX - 140, 480, 20, WHITE);
    DrawText("Flecha ARRIBA: Subir volumen", centroX - 140, 520, 20, LIGHTGRAY);
    DrawText("Flecha ABAJO: Bajar volumen", centroX - 140, 545, 20, LIGHTGRAY);

    // Instrucción volver al menú
    DrawText("BACKSPACE: Volver al menú", 30, 30, 20, YELLOW);

    // Texto parpadeante "Presiona nueva tecla..."
    if (esperando_tecla && mostrar_texto_parpadeante < 15) {
        DrawText("Presiona nueva tecla...", centroX - MeasureText("Presiona nueva tecla...", 20)/2, 570, 20, YELLOW);
    }

    if (mostrarMensajeTeclaUsada) {
        int centroX = 650;
        char* texto = "TECLA YA UTILIZADA";
        DrawText(texto, centroX - MeasureText(texto, 30)/2, 600, 30, RED);
    }
}

char* nombreTecla(int key) {
    switch (key) {
        case KEY_SPACE:
            return "SPACE";
        case KEY_LEFT_SHIFT:
            return "LEFT SHIFT";
        case KEY_RIGHT_SHIFT:
            return "RIGHT SHIFT";
        case KEY_LEFT_CONTROL:
            return "CTRL IZQ";
        case KEY_RIGHT_CONTROL:
            return "CTRL DER";
        case KEY_ENTER:
            return "ENTER";
        case KEY_BACKSPACE:
            return "BACKSPACE";
        case KEY_TAB:
            return "TAB";
        case KEY_UP:
            return "UP";
        case KEY_DOWN:
            return "DOWN";
        case KEY_LEFT:
            return "LEFT";
        case KEY_RIGHT:
            return "RIGHT";
        default: {
            char* n = GetKeyName(key);
            if (n == NULL || n[0] == '\0') return "UNKNOWN";
            else return n;
        }
    }
}

bool teclaAsignada(int key) {
    if (key == tecla_izquierda)
        return true;
    if (key == tecla_derecha)
        return true;
    if (key == tecla_salto)
        return true;
    if (key == tecla_agachar)
        return true;
    if (key == tecla_correr)
        return true;
    return false;
}

