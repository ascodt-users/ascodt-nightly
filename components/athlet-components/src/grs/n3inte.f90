      SUBROUTINE N3INTE ( ITERNB,LINIK,QNKI )
      USE CCA,    ONLY: L3DNK,DT,T
      USE CCAC,   ONLY: TFFKT,TFFKT0,T0TRNS
      USE CCC,    ONLY: KEYA1,KEYE,KEYOUT
      USE CGCO,   ONLY: TE
      USE CHCD,   ONLY: NKHCO
      USE CHCO,   ONLY: HC,HCTIME
      USE CHCP,   ONLY: IAHO, LHCU, LHLENG, POWERN,NRODS
      USE CNI ,   ONLY: NKSGMX, NNRODK
      USE CNK,    ONLY: INITIA
      USE CNR ,   ONLY: QNKI0
      USE CRCI,   only: QROD0 
      USE grs_AthletImplementation
      LOGICAL LINIK
      real(8),DIMENSION(NKSGMX)::QNKI
      call  athlet_instance%log%info("grs.Athlet", "n3inte() - entry")
      call  athlet_instance%n3inte%n3inte_transferCCA(L3DNK,DT,T)
      call  athlet_instance%n3inte%n3inte_transferCCAC(TFFKT,TFFKT0,T0TRNS)
      call  athlet_instance%n3inte%n3inte_transferCCC(KEYA1,KEYE,KEYOUT)
      call athlet_instance%n3inte%n3inte_transferCGCO(TE)
      call athlet_instance%n3inte%n3inte_transferCHCD(NKHCO,size(NKHCO))
      call  athlet_instance%n3inte%n3inte_transferCHCO(HC,size(HC),HCTIME)
      !POWERN
      call  athlet_instance%n3inte%n3inte_transferCHCP(IAHO,size(IAHO),LHCU,LHLENG,POWERN,size(POWERN),NRODS)
      call athlet_instance%n3inte%n3inte_transferCNI(NKSGMX,NNRODK)
      call  athlet_instance%n3inte%n3inte_transferCNK(INITIA)
      call  athlet_instance%n3inte%n3inte_transferCNR(QNKI0,size(QNKI0))
      call  athlet_instance%n3inte%n3inte_transferCRCI(QROD0,size(QROD0))
      call  athlet_instance%n3inte%n3inte_invoke(ITERNB,LINIK,QNKI,size(QNKI))
      call  athlet_instance%n3inte%n3inte_transferResults(POWERN,size(POWERN),QNKI0,size(QNKI0),INITIA)
      call athlet_instance%log%info("grs.Athlet", "n3inte() - exit")
      END
