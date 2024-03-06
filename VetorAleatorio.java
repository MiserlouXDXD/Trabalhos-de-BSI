import java.util.Random;

public class VetorAleatorio{
    public static int[] geraVetor(int tamanho, int valorMinimo, int valorMaximo) {
        if (tamanho <= 0 || valorMinimo > valorMaximo) {
            return null;
        }

        int[] vetor = new int[tamanho];
        Random random = new Random();

        for (int i = 0; i < tamanho; i++) {
            int valorAleatorio = random.nextInt(valorMaximo - valorMinimo + 1) + valorMinimo;
            vetor[i] = valorAleatorio;
        }

        return vetor;
    }

    public static void main(String[] args) {
        int tamanho = 100;
        int valorMinimo = 10;
        int valorMaximo = 50;

        int[] vetorAleatorio = geraVetor(tamanho, valorMinimo, valorMaximo);

        if (vetorAleatorio != null) {
            // Exibindo o vetor gerado
            for (int valor : vetorAleatorio) {
                System.out.print(valor + " ");
            }
        } else {
            System.out.println("Valores de entrada inválidos. O vetor não foi gerado.");
        }
    }
}
