<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="2.0">
    <xsl:output method="xml"/>
    <xsl:strip-space elements="*" />
    <xsl:template match="node()|@*">
        <xsl:copy>
            <xsl:apply-templates select="(node() except (id|mentioned|attributes))|@*"/>
        </xsl:copy>
    </xsl:template>
</xsl:stylesheet>
