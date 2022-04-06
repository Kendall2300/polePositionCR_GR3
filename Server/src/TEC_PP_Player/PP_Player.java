package TEC_PP_Player;

public class PP_Player {
    int id;
    int vidas;
    int score;
    boolean is_alive;
    int car_speed;
    boolean bulletHit=false;

    public int idSet(int num){
        return id+=num;
    }
    public int getId(){
        return id;
    }
    public int getVidas(){
        return vidas;
    }
    public void updateVidas(){
        this.vidas--;
    }
    public void setIs_dead(){
        if (vidas == 0){
            is_alive=false;
        }
    }
    public boolean getIs_alive(){
        return is_alive;
    }
    public int getScore(){
        return score;
    }
    public void bulletHit(boolean hited){
        if (hited==true){
            updateVidas();
        }else{

        }
    }
}