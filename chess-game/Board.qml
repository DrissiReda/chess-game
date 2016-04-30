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
        property variant blackPcs: { 'pawn' : [[6, 0], [6, 1], [6, 2], [6, 3], [6, 4], [6, 5], [6, 6], [6, 7]],
                                     'rook' : [[7, 0], [7, 7]],
                                     'knight' : [[7, 1], [7, 6]],
                                     'bishop' : [[7, 2], [7, 5]],
                                     'queen' : [[7, 3]],
                                     'king' : [[7, 4]]
                                       }

        property variant whitePcs: {

                                     'bishop' : [[0, 2], [0, 5]],
                                     'king'   : [[0, 4]],
                                     'knight' : [[0, 1], [0, 6]],
                                     'pawn'   : [[1, 0], [1, 1], [1, 2], [1, 3], [1, 4], [1, 5], [1, 6], [1, 7]],
                                     'queen'  : [[0, 3]],
                                     'rook'   : [[0, 0], [0, 7]]

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
            function availableMove(x,y)
            {

                (!((x+7-y) % 2))
                ? grid.children[x].children[7-y].children[0].source="images/avail_light.png"
                : grid.children[x].children[7-y].children[0].source="images/avail_dark.png";
                return 0;

                }
            function threatPiece(x,y)
            {
                    var j=0;

                   for(var prop in grid.whitePcs)
                   {
                        for(var i=0;i<grid.whitePcs[prop].length;i++)
                        {

                            j++;
                            console.log(grid.children[j] + " " + j );


                            if(grid.whitePcs[prop][i][0] === x && grid.whitePcs[prop][i][1] === y)
                               {
                                console.log(root.children[0].source);

                                root.children[j].source="images/Threat_"+prop+".png";



                                }
                            }
                   }



                   j=0;
                   for(prop in grid.blackPcs)
                   {

                        for(i=0;i<grid.blackPcs[prop].length;i++)
                        {
                            j++;
                            if(grid.blackPcs[prop][i][0] == x && grid.blackPcs[prop][i][1] == y)
                            {

                                root.children[j].source="images/Threat_"+prop+".png";
                                return 0;
                             }
                        }
                   }
                   return 0;
            }

            Rectangle {
                    width : grid.threatPiece(0,3);
                }
    }


    /* ====================== Pieces du jeu ====================== */

    /* ============ Pieces blanches ================= */




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
        /* ========= Roi Blanc ============== */
        Image {
            id: white_king
            width: 45; height: 45
            source: "images/white_king.png"
            x: grid.getX(4)
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

        Repeater{
            model: 8

          /* ==== Pions Blancs ========== */
        Image {
            id: white_pawn
            width: 45; height: 45
            source: "images/white_pawn.png"
            x: grid.getX(index)
            y: grid.getY(1)

        }
    }
    /* ======= Reine blanche =========== */
    Image {
        id: white_queen
        width: 45; height: 45
        source: "images/white_queen.png"
        x: grid.getX(3)
        y: grid.getY(0)
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


