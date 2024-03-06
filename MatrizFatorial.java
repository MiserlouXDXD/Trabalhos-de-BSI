public class MatrizFatorial {
    public static long fatorial(int numero) {
        if (numero < 0) {
            throw new IllegalArgumentException("Fatorial de número negativo não é definido.");
        }
        if (numero == 0 || numero == 1) {
            return 1;
        }
        long resultado = 1;
        for (int i = 2; i <= numero; i++) {
            resultado *= i;
        }
        return resultado;
    }

    public static void atualizarMatrizComFatorial(int[][] matriz) {
        int linhas = matriz.length;
        int colunas = matriz[0].length;

        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {
                matriz[i][j] = (int) fatorial(matriz[i][j]);
            }
        }
    }

    public static void imprimirMatriz(int[][] matriz) {
        for (int i = 0; i < matriz.length; i++) {
            for (int j = 0; j < matriz[0].length; j++) {
                System.out.print(matriz[i][j] + " ");
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        int[][] matriz = {
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9}
        };

        System.out.println("Matriz original:");
        imprimirMatriz(matriz);

        atualizarMatrizComFatorial(matriz);

        System.out.println("\nMatriz com fatoriais:");
        imprimirMatriz(matriz);
    }
}
