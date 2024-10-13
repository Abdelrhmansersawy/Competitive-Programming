# Game theory

## Terminology

1.  Depending into piece that every player can play
  
  1. **Partisan games**: some moves are available to one player and not to the other.
    
    - For example, in Chess, only one player can move the white pieces
      
  2. **Impartial games**: is a game in which the allowable moves depend only on the position and not on which of the two players is currently moving, and where the payoffs are symmetric
    
    - For example: Nim game
      
2. Depending into information that each player knows about the other player
  
  1. **Perfect information**: is a game of perfect information, as players know the private cards of their opponents.
    
    - For example: chess
      
  2.  **Imperfect information:** is a game of imperfect information, as players do not know the private cards of their opponents.
    
    - Card game
      

---

# Game variations

1. **Two player** vs Many player
  
2. **Sequantial** vs Simultaneous (eg. Rock paper Scissors)
  
3. **Prefect information** vs Imperfect
  
4. **Finite game** vs Infinate game
  
5. **Discreate game** vs continuous game
  
6. **Impartial game** vs Partisan game
  
7. **No randomizations** vs Randomizations
  
8. **Combinatorial** vs Non combinatorial game
  

Our focus only **bold** words

---

# Position properties

1. **Winning position**: From current position move to any losing position.
  
2. **Losing position**: From current position all moves are wining position.
  
3. **Terminal postion**: losing position -> base case.
  

---

# Playing strategy

1. **Duplicate**: It's like a mirror way, so we create a symmatric behaviour.
  
  - For example: Bowling Pins, [Black out problem](http://www.cse.yorku.ca/acm/Problems/2012-10-31/problemset.pdf)
    
2. **Cancellation**: The player cancels the other player move to keep the game into the same state.
  
  - For example: nim game
    

---

# Game types

- **Search techniques with pruning**: like using a dyamic programming.
  
- **Impartial game**: you can expected the output without doing search.
  

---

# Moore's nim-k

Generalization of nim, given $N$ piles and $K$

- Remove stones from any $K$ piles
  
- Expand evey pile size in base $2$
  

Game strategy, rhe 1-th player loses iff piles sum $\equiv 0\mod(k+1)$
