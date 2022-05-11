import java.io.IOException;

public class TestCsv {
    public static void main(String[] args) throws IOException {
        Csv test = new Csv();
        // System.out.println(-1);
        while (test.readLine() != null) {
            int nfield = test.getNfield();
            for (int i = 0; i < nfield; ++i) {
                // System.out.printf("field[%d] = '%s'\n", i, test.fieldAt(i));
                test.fieldAt(i);
            }
        }
    }

}
