<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema" version="2.0" exclude-result-prefixes="xs">
    <xsl:output method="xml" cdata-section-elements="svg html"/>
    <xsl:strip-space elements="*"/>
    <xsl:template match="/spec/errors">
        <xsl:copy>
            <xsl:apply-templates select="error"/>
            <xsl:for-each select="//step[signature='creates' and result]">
                <xsl:variable name="binding" select="result"/>
                <xsl:variable name="type" select="ancestor::method/bindings/binding[name=$binding]/type"/>
                <xsl:if test="/spec/types/type[name=$type and actor='true']">
                    <error type="semantic" pos="0">
                        <xsl:attribute name="line">
                            <xsl:value-of select="mentioned/where[1]"/>
                        </xsl:attribute>
                        <xsl:text>&quot;</xsl:text>
                        <xsl:value-of select="$type/name"/>
                        <xsl:text>&quot; can't be created in step &quot;</xsl:text>
                        <xsl:value-of select="number"/>
                        <xsl:text>&quot; because it is an actor</xsl:text>
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
