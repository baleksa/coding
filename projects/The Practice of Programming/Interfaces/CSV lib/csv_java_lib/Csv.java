import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.Vector;

public class Csv {
    private String line;
    private Vector<String> field = new Vector<String>();
    private final String fieldsep = ",";
    private int nfield;
    BufferedReader input;

    public Csv() {
        input = new BufferedReader(new InputStreamReader(System.in));
    }

    public Csv(final InputStream istream) {
        input = new BufferedReader(new InputStreamReader(istream));
    }

    public Csv(final File file) throws FileNotFoundException {
        input = new BufferedReader(new FileReader(file));
    }

    public String readLine() throws IOException {
        line = input.readLine();
        split();
        return line;
    }

    public int getNfield() {
        return nfield;
    }

    public String fieldAt(final int i) throws IndexOutOfBoundsException {
        if (i < 0 || i > nfield)
            throw new IndexOutOfBoundsException("Negative or too big index!");
        return field.get(i);
    }

    private int split() {
        if (line == null || line.length() == 0)
            return 0;
        nfield = 0;
        int i = 0;
        int j = 0;
        StringBuffer buffer = new StringBuffer();

        do {
            if (i < line.length() && line.charAt(i) == '"') {
                j = advquoted(buffer, ++i);
            } else {
                j = advplain(buffer, i);
            }
            if (nfield >= field.size()) {
                field.add(buffer.toString());
            } else {
                field.add(nfield, buffer.toString());
            }
            ++nfield;
            i = j + 1;
        } while (j < line.length());
        return nfield;
    }

    private int advplain(StringBuffer buffer, final int i) {
        buffer.setLength(0);
        int k = line.indexOf(fieldsep, i);
        if (k == -1)
            k = line.length();
        buffer.append(line.substring(i, k));
        return k;
    }

    private int advquoted(StringBuffer buffer, final int i) {
        buffer.setLength(0);
        int k = -1;
        for (int j = i; j < line.length(); ++j) {
            if (line.charAt(j) == '"' && (++j == line.length() || line.charAt(j) != '"')) {
                k = line.indexOf(fieldsep, j);
                if (k == -1)
                    k = line.length();
                buffer.append(line.substring(i, k));
                break;
            }
            buffer.append(line.charAt(j));
        }
        return k;
    }
}
