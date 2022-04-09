package TEC_PP_Player;

/**
 * @author kendall Martinez Carvajal kendallmc@estudiantec.cr
 */
public class PP_Jugadores {
    public int inicio;
    public int vidas;
    public int score;
    public int x_pos;
    public int y_pos;
    public int diferencia_y;

    /**
     * Este es el metodo constructor de la clase de jugadores este se encarga funcionar como un inicializador vacio
     */
    public PP_Jugadores(){
    }

    /**
     * Este metodo se encarga de construir un objeto de tipo jugadores aunque este constructor recibe como parametro
     * cada uno de los valores que se ocupan para la clase.
     * @param _inicio
     * @param c_vidas
     * @param ac_score
     * @param pos_x
     * @param pos_y
     * @param y_dif
     */
    public PP_Jugadores(int _inicio, int c_vidas, int ac_score, int pos_x, int pos_y, int y_dif){
        this.inicio=_inicio;
        this.vidas=c_vidas;
        this.score=ac_score;
        this.x_pos=pos_x;
        this.y_pos=pos_y;
        this.diferencia_y=y_dif;
    }
}
