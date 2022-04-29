import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.Reader;
import java.io.StreamTokenizer;
import java.util.ArrayList;
import java.util.Hashtable;
import java.util.Random;

/**
 * Chain
 */
public class Chain {
    static final int NPREF = 2; // NPREF adjacent words from input
    static final String NONWORD = "\n";
    Hashtable<Prefix, ArrayList<String>> statetab = new Hashtable<Prefix, ArrayList<String>>();
    Prefix prefix = new Prefix(NPREF, NONWORD);
    Random rand = new Random();

    public void build(InputStream in) throws IOException {
        Reader r = new BufferedReader(new InputStreamReader(in));
        StreamTokenizer st = new StreamTokenizer(r);

        st.resetSyntax();
        st.wordChars(0, Character.MAX_VALUE);
        st.whitespaceChars(0, ' ');
        while (st.nextToken() != StreamTokenizer.TT_EOF) {
            add(st.sval);
        }
        add(NONWORD);
    }

    private void add(String word) {
        ArrayList<String> suf = statetab.get(prefix);
        if (suf == null) {
            suf = new ArrayList<String>();
            statetab.put(new Prefix(prefix), suf);
        }
        suf.add(word);
        prefix.pref.remove(0);
        prefix.pref.add(word);
    }

    public void generate(int nwords) {
        Prefix pref = new Prefix(NPREF, NONWORD);
        for (int i = 0; i < nwords; i++) {
            ArrayList<String> suf = statetab.get(pref);
            int ind = rand.nextInt() % suf.size();
            String word = suf.get(ind);
            if (word == NONWORD)
                break;
            System.out.println(word);
            pref.pref.remove(0);
            pref.pref.add(word);
        }

    }
}

