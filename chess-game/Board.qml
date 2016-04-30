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
        property variant blackPcs: { 'pawns' : [[6, 0], [6, 1], [6, 2], [6, 3], [6, 4], [6, 5], [6, 6], [6, 7]],
                                     'rock' : [[7, 0], [7, 7]],
                                     'knights' : [[7, 1], [7, 6]],
                                     'bishop' : [[7, 2], [7, 5]],
                                     'queen' : [7, 3],
                                     'king' : [7, 4]
                                       }

        property variant whitePcs: { 'pawns' : [[1, 0], [1, 1], [1, 2], [1, 3], [1, 4], [1, 5], [1, 6], [1, 7]],
                                     'rock' : [[0, 0], [0, 7]],
                                     'knights' : [[0, 1], [0, 6]],
                                     'bishop' : [[0, 2], [0, 5]],
                                     'queen' : [0, 3],
                                     'king' : [0, 4]
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

    /* ============ Pieces blanches ================= */

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

    /* ==== Tours Blanches === */

    Image {
        id: white_rock1
        width: 45; height: 45
        source: "images/white_rook.png"
        x: grid.getX(0)
        y: grid.getY(0)
    }

    Image {
        id: white_rock2
        width: 45; height: 45
        source: "images/white_rook.png"
        x: grid.getX(7)
        y: grid.getY(0)
    }

    /* ===== Chevaux Blancs ======= */

    Image {
        id: white_knight1
        width: 45; height: 45
        source: "images/white_knight.png"
        x: grid.getX(1)
        y: grid.getY(0)
    }

    Image {
        id: white_knight2
        width: 45; height: 45
        source: "images/white_knight.png"
        x: grid.getX(6)
        y: grid.getY(0)
    }

    /* ======= Fous Blancs ======= */

    Image {
        id: white_bishop1
        width: 45; height: 45
        source: "images/white_bishop.png"
        x: grid.getX(2)
        y: grid.getY(0)
    }

    Image {
        id: white_bishop2
        width: 45; height: 45
        source: "images/white_bishop.png"
        x: grid.getX(5)
        y: grid.getY(0)
    }

    /* ======= Reine blanche =========== */
    Image {
        id: white_queen
        width: 45; height: 45
        source: "images/white_queen.png"
        x: grid.getX(3)
        y: grid.getY(0)
    }

    /* ========= Roi Blanc ============== */
    Image {
        id: white_king
        width: 45; height: 45
        source: "images/white_king.png"
        x: grid.getX(4)
        y: grid.getY(0)
    }


    /* ============ Pieces noires ================= */

    /* ==== Pions noirs ========== */

    Repeater{
        model: 8

        Image {
            id: black_pawn
            width: 45; height: 45
            source: "images/black_pawn.png"
            x: grid.getX(index)
            y: grid.getY(6)

        }
    }

    /* ==== Tours Blanches === */

    Image {
        id: black_rock1
        width: 45; height: 45
        source: "images/black_rook.png"
        x: grid.getX(0)
        y: grid.getY(7)
    }

    Image {
        id: black_rock2
        width: 45; height: 45
        source: "images/black_rook.png"
        x: grid.getX(7)
        y: grid.getY(7)
    }

    /* ===== Chevaux Blancs ======= */

    Image {
        id: black_knight1
        width: 45; height: 45
        source: "images/black_knight.png"
        x: grid.getX(1)
        y: grid.getY(7)
    }

    Image {
        id: black_knight2
        width: 45; height: 45
        source: "images/black_knight.png"
        x: grid.getX(6)
        y: grid.getY(7)
    }

    /* ======= Fous Blancs ======= */

    Image {
        id: black_bishop1
        width: 45; height: 45
        source: "images/black_bishop.png"
        x: grid.getX(2)
        y: grid.getY(7)
    }

    Image {
        id: black_bishop2
        width: 45; height: 45
        source: "images/black_bishop.png"
        x: grid.getX(5)
        y: grid.getY(7)
    }

    /* ======= Reine blanche =========== */
    Image {
        id: black_queen
        width: 45; height: 45
        source: "images/black_queen.png"
        x: grid.getX(3)
        y: grid.getY(7)
    }

    /* ========= Roi Blanc ============== */
    Image {
        id: black_king
        width: 45; height: 45
        source: "images/black_king.png"
        x: grid.getX(4)
        y: grid.getY(7)
    }
}


