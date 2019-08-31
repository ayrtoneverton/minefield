MACHINE
	Minefield
SETS
	MSG = { OK, ERROR, KILLED }
CONSTANTS
	MINE, NONE, TOTAL
PROPERTIES
	MINE : INT & NONE : INT & NONE < 0 & MINE < NONE & TOTAL : NAT1
VARIABLES
	sizeX, sizeY, FIELD
INVARIANT
	sizeX : NAT1 & sizeY : NAT1 & FIELD : 0..TOTAL --> INT
INITIALISATION
	FIELD := { 0 |-> NONE, 1 |-> NONE, 2 |-> MINE, 3 |-> NONE, 4 |-> NONE, 5 |-> NONE,
		6 |-> NONE, 7 |-> NONE, 8 |-> NONE, 9 |-> MINE, 10 |-> NONE, 11 |-> NONE }
	|| sizeX := 6
	|| sizeY := 2
OPERATIONS
	rr <-- select(xx, yy) =
		PRE xx : NAT & yy : NAT & xx < sizeX & yy < sizeY THEN
			IF FIELD(xx + sizeX * yy) = MINE THEN
				rr := KILLED
			ELSE
				FIELD := FIELD <+
					{ ii, jj | ii : closure({ kk, ll | ll : dom(FIELD)
							& FIELD(ll) = NONE
							& kk : dom(FIELD)
							& (kk mod sizeX) : (ll mod sizeX-1)..(ll mod sizeX+1)
							& (kk/sizeX) : (ll/sizeX-1)..(ll/sizeX+1)
							& FIELD(kk) = NONE
							& 0 = card({ aa, bb | aa : (kk mod sizeX-1)..(kk mod sizeX+1)
								& bb : (kk/sizeX-1)..(kk/sizeX+1)
								& aa >= 0
								& bb >= 0
								& aa < sizeX
								& bb < sizeY
								& FIELD(aa + sizeX * bb) = MINE })
						})[{ xx + sizeX * yy }]
						& jj = card({ aa, bb | aa : (ii mod sizeX-1)..(ii mod sizeX+1)
							& bb : (ii/sizeX-1)..(ii/sizeX+1)
							& aa >= 0
							& bb >= 0
							& aa < sizeX
							& bb < sizeY
							& FIELD(aa + sizeX * bb) = MINE
						})
					}
				|| rr := OK
			END
		END;
	rr <-- isWinner =
		IF #xx.(xx : dom(FIELD) & FIELD(xx) = NONE) THEN
			rr := ERROR
		ELSE
			rr := OK
		END;
	initField(ff) =
		PRE ff : 0..TOTAL --> INT THEN
			FIELD := ff
		END
END