# Open OnDemand Documentation Styleguide

## Headings

### Titles

Heading titles should capitalize every major word and lowercase
every minor word.

  * major words: Nouns, verbs (including linking verbs), adjectives, adverbs, pronouns, and all words of four letters or more are considered major words.

  * minor words: Short (i.e., three letters or fewer) conjunctions, short prepositions, and all articles are considered minor words.

### RST Title Underlines Characters

Sphinx rst files allow for any non-alphanumeric character to be the
title underlines. It will even allow for different pages to have different
conventions/underline characters for different sections.

Throughout this codebase title underlines are varied. However, at some point
we should standardize to this convention which `source/customizations.rst`
follows:

* H1: ===
* H2: ---
* H3: ...
* H4: ```
* H5: TBD

## Code-block spacing

The convention in RST for code-block spacing is to have the content
have 3 spaces as shown below.

```raw
  .. code-block:: sh

     sudo systemctl try-restart apache2
```

This project breaks that convention by using 2 spaces in the `code-block`
content as shown below.

```raw
  .. code-block:: sh

    sudo systemctl try-restart apache2
```

While this may look more visually applealing as the content is left aligned 
with the `code-block` text above it - text editors and IDEs show an extra space
at this point and it's a bit off putting.
