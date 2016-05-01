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
                return 45*x;
            }
            function getY(y){
                return (7 - y)*45;
            }
            function movePiece(piece)
            {
                x = piece.x / 45;
                y = (piece.y / 45) - 7;
                grid.children[x].children[y].children[0].source = ((x + y) % 2 == 0) ? "images/click_light" : "images/click_right";
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


                            if(grid.whitePcs[prop][i][0] === x && grid.whitePcs[prop][i][1] === y)
                               {

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


    }


    /* ====================== Pieces du jeu ====================== */

    /* ============ Pieces blanches ================= */




        /* ======= Fous Blancs ======= */

        Image {
            id: white_bishop1
            width: 45; height: 45
            source: mouseArea.containsMouse ?"images/Click_dark_white_bishop.png" : "images/white_bishop.png"
            x: grid.getX(2)
            y: grid.getY(0)


            MouseArea {
                    id : mouseArea
                    anchors.fill : parent
                    hoverEnabled : true
            }

        }
        Image {

            id: white_bishop2
            width: 45; height: 45
            source: mouseArea1.containsMouse ?"images/Click_light_white_bishop.png" : "images/white_bishop.png"
            x: grid.getX(5)
            y: grid.getY(0)
            MouseArea {
                    id : mouseArea1
                    anchors.fill : parent
                    hoverEnabled : true
            }

        }
        /* ========= Roi Blanc ============== */
        Image {
            id: white_king
            width: 45; height: 45
            source: mouseArea2.containsMouse ?"images/Click_dark_white_king.png" : "images/white_king.png"
            x: grid.getX(4)
            y: grid.getY(0)
            MouseArea {
                    id : mouseArea2
                    anchors.fill : parent
                    hoverEnabled : true
            }
        }
        /* ===== Chevaux Blancs ======= */

        Image {
            id: white_knight1
            width: 45; height: 45
            source: mouseArea3.containsMouse ?"images/Click_light_white_knight.png" : "images/white_knight.png"
            x: grid.getX(1)
            y: grid.getY(0)
            MouseArea {
                    id : mouseArea3
                    anchors.fill : parent
                    hoverEnabled : true
            }
        }

        Image {
            id: white_knight2
            width: 45; height: 45
            source: mouseArea4.containsMouse ?"images/Click_dark_white_knight.png" : "images/white_knight.png"
            x: grid.getX(6)
            y: grid.getY(0)
            MouseArea {
                    id : mouseArea4
                    anchors.fill : parent
                    hoverEnabled : true
            }
        }



          /* ==== Pions Blancs ========== */
        Image {
            id: white_pawn1
            width: 45; height: 45
            source: mouseArea51.containsMouse ?"images/Click_light_white_pawn.png" : "images/white_pawn.png"
            x: grid.getX(0)
            y: grid.getY(1)

            MouseArea {
                    id : mouseArea51
                    anchors.fill : parent
                    hoverEnabled : true
            }

        }
        Image {
            id: white_pawn2
            width: 45; height: 45
            source: mouseArea52.containsMouse ?"images/Click_dark_white_pawn.png" : "images/white_pawn.png"
            x: grid.getX(1)
            y: grid.getY(1)
            MouseArea {
                    id : mouseArea52
                    anchors.fill : parent
                    hoverEnabled : true
            }

        }
        Image {
            id: white_pawn3
            width: 45; height: 45
            source: mouseArea53.containsMouse ?"images/Click_light_white_pawn.png" : "images/white_pawn.png"
            x: grid.getX(2)
            y: grid.getY(1)
            MouseArea {
                    id : mouseArea53
                    anchors.fill : parent
                    hoverEnabled : true
            }

        }
        Image {
            id: white_pawn4
            width: 45; height: 45
           source: mouseArea54.containsMouse ?"images/Click_dark_white_pawn.png" : "images/white_pawn.png"
            x: grid.getX(3)
            y: grid.getY(1)
            MouseArea {
                    id : mouseArea54
                    anchors.fill : parent
                    hoverEnabled : true
            }

        }
        Image {
            id: white_pawn5
            width: 45; height: 45
            source: mouseArea55.containsMouse ?"images/Click_light_white_pawn.png" : "images/white_pawn.png"
            x: grid.getX(4)
            y: grid.getY(1)
            MouseArea {
                    id : mouseArea55
                    anchors.fill : parent
                    hoverEnabled : true
            }

        }
        Image {
            id: white_pawn6
            width: 45; height: 45
            source: mouseArea56.containsMouse ?"images/Click_dark_white_pawn.png" : "images/white_pawn.png"
            x: grid.getX(5)
            y: grid.getY(1)
            MouseArea {
                    id : mouseArea56
                    anchors.fill : parent
                    hoverEnabled : true
            }

        }
        Image {
            id: white_pawn7
            width: 45; height: 45
            source: mouseArea57.containsMouse ?"images/Click_light_white_pawn.png" : "images/white_pawn.png"
            x: grid.getX(6)
            y: grid.getY(1)
            MouseArea {
                    id : mouseArea57
                    anchors.fill : parent
                    hoverEnabled : true
            }

        }
        Image {
            id: white_pawn8
            width: 45; height: 45
            source: mouseArea58.containsMouse ?"images/Click_dark_white_pawn.png" : "images/white_pawn.png"
            x: grid.getX(7)
            y: grid.getY(1)
            MouseArea {
                    id : mouseArea58
                    anchors.fill : parent
                    hoverEnabled : true
            }

        }

    /* ======= Reine blanche =========== */
    Image {
        id: white_queen
        width: 45; height: 45
        source: mouseArea6.containsMouse ?"images/Click_light_white_queen.png" : "images/white_queen.png"
        x: grid.getX(3)
        y: grid.getY(0)
        MouseArea {
                id : mouseArea6
                anchors.fill : parent
                hoverEnabled : true
        }
    }


    /* ==== Tours Blanches === */

    Image {
        id: white_rock1
        width: 45; height: 45
       source: mouseArea7.containsMouse ?"images/Click_dark_white_rook.png" : "images/white_rook.png"
        x: grid.getX(0)
        y: grid.getY(0)
        MouseArea {
                id : mouseArea7
                anchors.fill : parent
                hoverEnabled : true
        }
    }

    Image {
        id: white_rock2
        width: 45; height: 45
        source: mouseArea8.containsMouse ?"images/Click_light_white_rook.png" : "images/white_rook.png"
        x: grid.getX(7)
        y: grid.getY(0)
        MouseArea {
                id : mouseArea8
                anchors.fill : parent
                hoverEnabled : true
        }
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


