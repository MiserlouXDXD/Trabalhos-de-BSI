import java.util.Arrays;
import java.util.Random;
import java.util.Scanner;

public class OrdenacaoVetores {
    public static void constroiVetor(int[] vetor, int tamanho) {
        Random random = new Random();
        for (int i = 0; i < tamanho; i++) {
            vetor[i] = random.nextInt(20); // Preenche o vetor com valores inteiros aleatórios
        }
    }

    public static void apresentaVetor(int[] vetor) {
        for (int elemento : vetor) {
            System.out.print(elemento + " ");
        }
        System.out.println();
    }

    public static void bubbleSort(int[] vetor) {
        int n = vetor.length;
        boolean trocado;
        do {
            trocado = false;
            for (int i = 1; i < n; i++) {
                if (vetor[i - 1] > vetor[i]) {
                    int temp = vetor[i - 1];
                    vetor[i - 1] = vetor[i];
                    vetor[i] = temp;
                    trocado = true;
                }
            }
        } while (trocado);
    }

    public static void shellSort(int[] vetor) {
        int n = vetor.length;
        for (int intervalo = n / 2; intervalo > 0; intervalo /= 2) {
            for (int i = intervalo; i < n; i++) {
                int temp = vetor[i];
                int j;
                for (j = i; j >= intervalo && vetor[j - intervalo] > temp; j -= intervalo) {
                    vetor[j] = vetor[j - intervalo];
                }
                vetor[j] = temp;
            }
        }
    }

    public static void organizaVetor1(int[] vetor) {
        System.out.println("Vetor original:");
        apresentaVetor(vetor);
        bubbleSort(vetor);
        System.out.println("Ordenado com Bubble Sort:");
        apresentaVetor(vetor);
    }

    public static void organizaVetor2(int[] vetor) {
        System.out.println("Vetor original:");
        apresentaVetor(vetor);
        shellSort(vetor);
        System.out.println("Ordenado com Shell Sort:");
        apresentaVetor(vetor);
    }

    public static void organizaVetor3(int[] vetor) {
        System.out.println("Vetor original:");
        apresentaVetor(vetor);
        Arrays.sort(vetor);
        System.out.println("Ordenado com Quick Sort (Arrays.sort()):");
        apresentaVetor(vetor);
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int tamanho = 5;
        int[] vetor = new int[tamanho];

        constroiVetor(vetor, tamanho);

        System.out.println("Escolha o algoritmo de ordenação:");
        System.out.println("1 - Bubble Sort");
        System.out.println("2 - Shell Sort");
        System.out.println("3 - Quick Sort (usando Arrays.sort())");

        int opcao = scanner.nextInt();

        int[] vetorOrdenado = Arrays.copyOf(vetor, vetor.length);

        switch (opcao) {
            case 1:
                organizaVetor1(vetorOrdenado);
                break;
            case 2:
                organizaVetor2(vetorOrdenado);
                break;
            case 3:
                organizaVetor3(vetorOrdenado);
                break;
            default:
                System.out.println("Opção inválida.");
        }
    }
}
