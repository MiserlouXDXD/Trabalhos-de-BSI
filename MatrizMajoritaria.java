import java.util.Random;

public class MatrizMajoritaria {
    public static int[][] criarMatrizAleatoria(int linhas, int colunas, int minimo, int maximo) {
        int[][] matriz = new int[linhas][colunas];
        Random random = new Random();

        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {
                matriz[i][j] = random.nextInt(maximo - minimo + 1) + minimo;
            }
        }

        return matriz;
    }

    public static boolean matrizMajoritaria(int[][] matriz) {
        int linhas = matriz.length;
        int colunas = matriz[0].length;
        int metadeDimensao = linhas * colunas / 2;

        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {
                int valorAtual = matriz[i][j];
                int contagem = 0;

                for (int k = 0; k < linhas; k++) {
                    for (int l = 0; l < colunas; l++) {
                        if (matriz[k][l] == valorAtual) {
                            contagem++;
                        }
                    }
                }

                if (contagem > metadeDimensao) {
                    return true;
                }
            }
        }

        return false;
    }

    public static void main(String[] args) {
        int linhas = 3;
        int colunas = 3;
        int minimo = 1;
        int maximo = 5;

        int[][] matriz = criarMatrizAleatoria(linhas, colunas, minimo, maximo);

        System.out.println("Matriz gerada:");
        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {
                System.out.print(matriz[i][j] + " ");
            }
            System.out.println();
        }

        boolean majoritaria = matrizMajoritaria(matriz);
        System.out.println("A matriz é majoritária? " + majoritaria);
    }
}
