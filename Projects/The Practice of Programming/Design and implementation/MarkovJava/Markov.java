import java.io.IOException;

public class Markov {
    static final int MAXGEN = 10000;
    public static void main(String[] args) {
        Chain chain = new Chain();
        int nwords = MAXGEN;

        try {
            chain.build(System.in);
        } catch (IOException e) {
            e.printStackTrace();
        }
        chain.generate(nwords);
    }
}


