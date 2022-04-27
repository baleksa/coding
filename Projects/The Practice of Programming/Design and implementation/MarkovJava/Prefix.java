import java.util.ArrayList;

class Prefix {
    public ArrayList<String> pref;

    public Prefix(int n, String word) {
        for (int i = 0; i < n; i++) {
            pref.add(word);
        }
    }

    @SuppressWarnings("unchecked")
    public Prefix(Prefix other) {
        if (other != null)
            pref = (ArrayList<String>) other.pref.clone();

    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        for (int i = 0; i < pref.size(); i++) {
            result = prime * result + pref.get(i).hashCode();
        }
        return result;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj)
            return true;
        if (obj == null)
            return false;
        if (getClass() != obj.getClass())
            return false;
        Prefix other = (Prefix) obj;
        if (pref == null) {
            if (other.pref != null)
                return false;
        } else {
            if (pref.size() != other.pref.size())
                return false;
            for (int i = 0; i < pref.size(); i++) {
                if (pref.get(i) != other.pref.get(i))
                    return false;
            }
        }
        return true;
    }
        return tr}
    }
}
