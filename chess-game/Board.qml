/*
  board.qml
  =========

  Crée le : 24 avril 2016

  affiche l'échiquier avec les pieces

 */


/*
  Notes
  =====

  Contrairement à la representation classique matricielle ou on parcourt d'abord la ligne et puis les colonnes
  J'ai adopté le contraire => collones puis lignes (la representation classique ne marche pas :x )

*/


import QtQuick 2.4
import QtQuick.Layouts 1.3

Item {
    id: root
    width: 8*45
    height: 8*45

    GridLayout {
        id: grid
        columnSpacing: 0

        //Deux dictionnaires qui contiennt les positions des pieces blanches et noires
        property variant whitePcs: { 'white_pawns' : [[1, 0], [1, 1], [1, 2], [1, 3], [1, 4], [1, 5], [1, 6], [1, 7]]
                                       }
        //generation des divers case via deux Repeaters : le premier pour les lignes, le deuxieme pour les collones
        Repeater {
            model: 8 //8 lignes

            Column {
                id: currentCol
                property int colIndex: index //Une propriété qui permettera par la suite d'alterner les couleurs suivants les lignes

                Repeater {
                    model: 8 //8 cases par ligne

                    Row {
                        id: currentRow
                        property int colIndex: index //Une propriété qui permettera d'identifier les cases par la suite

                        Image{
                            width: 45; height: 45 //Chaque case fait 45x45 (téléchargé depuis Wikipedia
                            //Les cases dont la somme de la ligne et la colonne est paire sont blanches, ceux impaires doivent etre noir
                            source: ( (index + currentCol.colIndex) % 2 == 0)  ? "images/light_square.png" : "images/dark_square.png"
                        }

                    }

                 }
             }
        }


            /* =================== Fonctions =========================== */

            function getX(x){
                return 45*x
            }
            function getY(y){
                return (7 - y)*45;
            }
    }

    /* ====================== Pieces du jeu ====================== */

    /* ==== Pions Blancs ========== */

    Repeater{
        model: 8

        Image {
            id: white_pawn
            width: 45; height: 45
            source: "images/white_pawn.png"
            x: grid.getX(index)
            y: grid.getY(1)

        }
    }

}


