# fuzzy_string_search
Implementation of a fuzzy dictionary search algorithm using an n-gram index.

Example:

```
// Set words we want to use in fuzzy search
NgramBuilder builder("../../src/ngram/words_alpha.txt");

NgramSearcher searcher(&builder);

std::vector<std::string> match = searcher.get_best_match("latitude");

for(auto& item : match)
{
    std::cout << item << "\n";
}
```

Output:

```
colatitude
latitude
latitudes
midlatitude
platitude
platitudes
platitudinisation
platitudinization
```
