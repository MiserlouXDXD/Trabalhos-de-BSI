import java.util.Random;

public class MatrizSepararParImpar {

    public static int[][] geraMatriz(int m, int n) {
        Random random = new Random();
        int[][] matriz = new int[m][n];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                matriz[i][j] = random.nextInt(100);  // Preenche a matriz com valores inteiros aleatórios
            }
        }
        return matriz;
    }

    public static int[] separaParesImpares(int[][] matriz) {
        int m = matriz.length;
        int n = matriz[0].length;
        int numPares = 0;
        int numImpares = 0;

        // Conta o número de elementos pares e ímpares na matriz
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matriz[i][j] % 2 == 0) {
                    numPares++;
                } else {
                    numImpares++;
                }
            }
        }

        int[] resultado = new int[numPares + numImpares];
        int indexPares = 0;
        int indexImpares = numPares;

        // Preenche o vetor com os elementos pares e ímpares
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matriz[i][j] % 2 == 0) {
                    resultado[indexPares] = matriz[i][j];
                    indexPares++;
                } else {
                    resultado[indexImpares] = matriz[i][j];
                    indexImpares++;
                }
            }
        }

        return resultado;
    }

    public static void main(String[] args) {
        int m = 3; // Número de linhas
        int n = 4; // Número de colunas

        int[][] matriz = geraMatriz(m, n);

        System.out.println("Matriz gerada:");
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                System.out.print(matriz[i][j] + " ");
            }
            System.out.println();
        }

        int[] resultado = separaParesImpares(matriz);

        System.out.println("\nElementos pares e ímpares separados:");
        for (int num : resultado) {
            System.out.print(num + " ");
        }
    }
}
