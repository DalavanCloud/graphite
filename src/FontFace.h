#ifndef FONTFACE_INCLUDE
#define FONTFACE_INCLUDE

#include "GlyphFace.h"
#include "Silf.h"
#include "TtfUtil.h"
#include "Main.h"
#include "graphiteng/IFace.h"
#include "FeatureMap.h"

class Segment;

#define ktiCmap MAKE_TAG('c','m','a','p')
#define ktiHead MAKE_TAG('h','e','a','d')
#define ktiGlyf MAKE_TAG('g','l','y','f')
#define ktiHdmx MAKE_TAG('h','d','m','x')
#define ktiHhea MAKE_TAG('h','h','e','a')
#define ktiHmtx MAKE_TAG('h','m','t','x')
#define ktiLoca MAKE_TAG('l','o','c','a')
#define ktiKern MAKE_TAG('k','e','r','n')
#define ktiMaxp MAKE_TAG('m','a','x','p')
#define ktiName MAKE_TAG('n','a','m','e')
#define ktiOs2  MAKE_TAG('O','S','/','2')
#define ktiPost MAKE_TAG('p','o','s','t')
#define ktiFeat MAKE_TAG('F','e','a','t')
#define ktiGlat MAKE_TAG('G','l','a','t')
#define ktiGloc MAKE_TAG('G','l','o','c')
#define ktiSilf MAKE_TAG('S','i','l','f')
#define ktiSile MAKE_TAG('S','i','l','e')
#define ktiSill MAKE_TAG('S','i','l','l')

class FontFace 
{
public:
    virtual void *getTable(unsigned int name, size_t *len) { return m_face->getTable(name, len); }
    virtual float advance(unsigned short id);
    virtual Silf *silf(int i) { return ((i < m_numSilf) ? m_silfs + i : (Silf *)NULL); }
    virtual void runGraphite(Segment *seg, Silf *silf);
    virtual uint16 findPseudo(uint32 uid) { m_numSilf ? m_silfs[0].findPseudo(uid) : 0; }

public:
    FontFace(IFace *face) : m_face(face) {}
    GlyphFace *glyph(unsigned short glyphid) { return m_glyphs + glyphid; } // m_glyphidx[glyphid]; }
    float getAdvance(unsigned short glyphid, float scale) { return advance(glyphid) * scale; }
    unsigned short upem() { return m_upem; }
    unsigned short numGlyphs() { return m_numGlyphs; }
    bool readGlyphs();
    bool readGraphite();
    bool readFeatures() { return m_features.readFont(m_face); }
    Silf *chooseSilf(uint32 script);

protected:

    IFace *m_face;                  // Where to get tables
    unsigned short m_numGlyphs;     // number of glyphs in the font
    // unsigned short *m_glyphidx;     // index for each glyph id in the font
    // unsigned short m_readglyphs;    // how many glyphs have we in m_glyphs?
    // unsigned short m_capacity;      // how big is m_glyphs
    GlyphFace *m_glyphs;            // list of actual glyphs indexed by glyphidx, 1 base
    unsigned short m_upem;          // design units per em
    unsigned short m_numAttrs;      // number of glyph attributes per glyph
    unsigned short m_numSilf;       // number of silf subtables in the silf table
    Silf *m_silfs;                   // silf subtables.
    FeatureMap m_features;
};

#endif // FONTFACE_INCLUDE
