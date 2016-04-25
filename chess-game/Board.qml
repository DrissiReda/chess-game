/*
  board.qml
  =========

  Crée le : 24 avril 2016

  affiche l'échiquier avec les pieces

 */

import QtQuick 2.4
import QtQuick.Layouts 1.3

GridLayout {
    id: root
    //generation des divers case via deux Repeaters : le premier pour les lignes, le deuxieme pour les collones
    Column {
        Repeater {
            model: 8 //8 lignes

            Row {
                id: currentRow
                property int rowIndex: index //Une propriété qui permettera par la suite d'alterner les couleurs suivants les lignes

                Repeater {
                    model: 8 //8 cases par ligne

                    Image{
                        width: 45; height: 45 //Chaque case fait 45x45 (téléchargé depuis Wikipedia
                        //Les cases dont la somme de la ligne et la colonne est paire sont blanches, ceux impaires doivent etre noir
                        source: ( (index + currentRow.rowIndex) % 2 == 0)  ? "images/light_square.png" : "images/dark_square.png"
                    }

                }

             }
         }
     }

}

