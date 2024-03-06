import java.util.Arrays;

public class Estatistica {
    static double desvioPadrao(double[] serie) {
        double variancia = variancia(serie);
        return Math.sqrt(variancia);
    }

    static double variancia(double[] serie) {
        double desvioQuadrado = desvioQuadrado(serie);
        return desvioQuadrado / (serie.length - 1);
    }

    static double desvioQuadrado(double[] serie) {
        double media = mediaAritmetica(serie);
        double soma = 0;
        for (double valor : serie) {
            soma += Math.pow(valor - media, 2);
        }
        return soma;
    }

    static double mediaAritmetica(double[] serie) {
        double soma = 0;
        for (double valor : serie) {
            soma += valor;
        }
        return soma / serie.length;
    }

    public static void main(String[] args) {
        int tamanho = 10;
        double[] serie = new double[tamanho];

        // Preencha a série com valores reais entre -10.0 e 10.0 (como no exemplo original)
        for (int i = 0; i < tamanho; i++) {
            serie[i] = -10.0 + Math.random() * 20.0;
        }

        System.out.println("Média Aritmética: " + mediaAritmetica(serie));
        System.out.println("Desvio Quadrado: " + desvioQuadrado(serie));
        System.out.println("Variância: " + variancia(serie));
        System.out.println("Desvio Padrão: " + desvioPadrao(serie));
    }
}
