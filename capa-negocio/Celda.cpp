/**
  * Celda representa una celda individual en un tablero de campo minado. 
  * Puede contener una mina, estar revelado, estar marcada o estar vacía.  
*/

#include <string>

class Celda {

    private:

        bool mina;
        int minas_adyacentes = 0;
        bool revelado = false;
        bool marcada = false;
        std::string signo = "";

    public:

        Celda() { mina = false;}
        Celda (bool minaEstado) {
            mina = minaEstado;
        }

        std::string getSigno() {return signo;}
        bool getReveladoEstado()  {return revelado;}
        bool getMinaEstado()  {return mina;}
        bool getMarcadaEstado()  {return marcada;}
        int getNumMinasAdyacentes() {return minas_adyacentes;}

        void setSigno(std::string nuevoSigno) {signo = nuevoSigno;}
        void setReveladoEstado(bool estado) {revelado = estado;}
        void setMarcadoEstado(bool estado) {
            if (!revelado) {marcada = estado;}
        }
        
        void sumarMinasAdyacentes() { minas_adyacentes++;}
};
