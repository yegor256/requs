<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema" version="2.0" exclude-result-prefixes="xs">
    <xsl:output method="xml" cdata-section-elements="svg html"/>
    <xsl:strip-space elements="*"/>
    <xsl:template match="/spec/errors">
        <xsl:copy>
            <xsl:apply-templates select="error"/>
            <xsl:for-each select="/spec/types/type">
                <xsl:variable name="type" select="."/>
                <xsl:if test="not(//binding/type=$type/name) and not(//slot/type=$type/name)">
                    <error type="seal" pos="0">
                        <xsl:attribute name="line">
                            <xsl:value-of select="$type/mentioned/where[1]"/>
                        </xsl:attribute>
                        <xsl:text>Type &quot;</xsl:text>
                        <xsl:value-of select="$type/name"/>
                        <xsl:text>&quot; is not used in any slot or a use case</xsl:text>
                    </error>
                </xsl:if>
            </xsl:for-each>
        </xsl:copy>
    </xsl:template>
    <xsl:template match="node()|@*">
        <xsl:copy>
            <xsl:apply-templates select="node()|@*"/>
        </xsl:copy>
    </xsl:template>
</xsl:stylesheet>
